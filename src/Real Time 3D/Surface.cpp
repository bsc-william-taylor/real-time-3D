
#include "Surface.h"
#include "Demo.h"

Surface::Surface() :
    shouldDraw(false),
    firstTime(true)
{
    matrix = NULL;
    vertexArray = NULL;
    vertexBuffer = NULL;
}

Surface::~Surface()
{
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);

    SAFE_RELEASE(matrix);
}

void Surface::enable()
{
    shouldDraw = GL_TRUE;
}

void Surface::disable()
{
    shouldDraw = GL_FALSE;
}

bool Surface::checkForCollision(Camera * camera)
{
    if (!surfaces.empty())
    {
        mat4 mat = matrix->getProjection() * matrix->getModel();
        vec3 position = camera->getPosition();
        for (unsigned int i = 0; i < surfaces.size(); i++)
        {
            if (surfaces[i]->collisionTest(mat, position))
            {
                return true;
            }
        }
    }

    return false;
}

bool Surface::checkForCollision(SubSurface* surface, Camera* camera)
{
    if (!surfaces.empty())
    {
        vec3 point = vec3(sin(RAIDAN(camera->getRotation())), 0, cos(RAIDAN(camera->getRotation())));
        vec3 position = camera->getPosition() + (point *= 5);
        mat4 mat = matrix->getProjection() * matrix->getModel();

        for (unsigned int i = 0; i < surfaces.size(); i++)
        {
            if (surfaces[i]->collisionTest(mat, position))
            {
                return true;
            }
        }
    }

    return false;
}

void Surface::setSize(vec3 pos, vec3 sz)
{
    positions.push_back(pos);
    size.push_back(sz);
}

void Surface::render()
{
    program->use();
    program->setMatrix("Projection", matrix->getProjection());
    program->setMatrix("Model", matrix->getModel());
    program->setMatrix("View", matrix->getView());

    glBindVertexArray(vertexArray);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, count);

    if (!Demo::demoSettings.wireframeEnabled) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glBindVertexArray(0);
    program->release();
}

void Surface::setup()
{
    program = ShaderManagerGL::get()->getShader("data/shaders/box.vert", "data/shaders/box.frag");

    vector<vec3> faces;
    faces.reserve(24 * surfaces.size());
    for (GLuint i = 0; i < surfaces.size(); i++)
    {
        vec3 p = surfaces[i]->getMeshPosition();
        vec3 s = surfaces[i]->getMeshSize();

        faces.push_back(vec3(p.x, p.y, p.z));
        faces.push_back(vec3(p.x, s.y, p.z));
        faces.push_back(vec3(s.x, s.y, p.z));
        faces.push_back(vec3(p.x, p.y, p.z));
        faces.push_back(vec3(s.x, p.y, p.z));
        faces.push_back(vec3(s.x, s.y, p.z));

        faces.push_back(vec3(p.x, p.y, s.z));
        faces.push_back(vec3(p.x, s.y, s.z));
        faces.push_back(vec3(s.x, s.y, s.z));
        faces.push_back(vec3(p.x, p.y, s.z));
        faces.push_back(vec3(s.x, p.y, s.z));
        faces.push_back(vec3(s.x, s.y, s.z));

        faces.push_back(vec3(p.x, p.y, p.z));
        faces.push_back(vec3(p.x, p.y, s.z));
        faces.push_back(vec3(p.x, s.y, s.z));
        faces.push_back(vec3(p.x, p.y, p.z));
        faces.push_back(vec3(p.x, s.y, p.z));
        faces.push_back(vec3(p.x, s.y, s.z));

        faces.push_back(vec3(s.x, p.y, p.z));
        faces.push_back(vec3(s.x, p.y, s.z));
        faces.push_back(vec3(s.x, s.y, s.z));
        faces.push_back(vec3(s.x, p.y, p.z));
        faces.push_back(vec3(s.x, s.y, p.z));
        faces.push_back(vec3(s.x, s.y, s.z));
    }

    count = faces.size();

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * faces.size(), &faces[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
}

void Surface::onUpdate(MatrixGL* trans)
{
    matrix = trans;

    if (firstTime)
    {
        auto newSurface = new SubSurface();
        auto meshNumber = 0;

        for (unsigned int i = 0; i < positions.size(); i++)
        {
            vec3 p = positions[i];
            vec3 s = size[i];

            if (!newSurface->passPoint(p, s) || meshNumber != -1 && i >= maxValues[meshNumber])
            {
                surfaces.push_back(newSurface);
                newSurface = new SubSurface();

                if (meshNumber + 1 < maxValues.size())
                {
                    meshNumber++;
                }
                else
                {
                    meshNumber = -1;
                }
            }
        }

        setup();

        firstTime = false;
    }
}

MatrixGL* Surface::getMatrix()
{
    return matrix;
}

void Surface::addMaxMeshes(int max)
{
    maxValues.push_back(max);
}

vector<SubSurface *>& Surface::getSubSurface()
{
    return surfaces;
}