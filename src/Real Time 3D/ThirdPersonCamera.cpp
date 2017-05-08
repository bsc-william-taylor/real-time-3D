
#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera()
{
    cameraTranslate = vec3(0.0, -2.0, 0.0);
    animatedModel = nullptr;
    cameraSpeed = vec3();

    animationStep = 0;
    animation = 0;
    rotation = .0f;
    pitch = .0f;
    y = .0f;
}

ThirdPersonCamera::~ThirdPersonCamera()
{

}

GLvoid ThirdPersonCamera::setPlayerModel(DynamicModel * m)
{
    animatedModel = m;
}

GLvoid ThirdPersonCamera::cancelMovement()
{
    movement = vec3(0, 0, 0);
}

void ThirdPersonCamera::onUpdate(bool updateModel)
{
    mat4 cameraMat = mat4(1.0f);
    cameraTranslate += movement;

    if (updateModel)
    {
        animatedModel->getMatrix()->rotateView(RAIDAN(pitch), vec3(1.0, 0.0, 0.0));
        animatedModel->getMatrix()->translateView(movement + vec3(0.0, -1.5, -3.0));
    }

    renderer->translateView(cameraTranslate);
    renderer->translateView(-cameraTranslate);
    renderer->rotateView(RAIDAN(pitch), vec3(1.0, 0.0, 0.0));
    renderer->rotateView(RAIDAN(rotation), vec3(0.0, 1.0, 0.0));
    renderer->translateView(cameraTranslate);

    cancelMovement();

    if (updateModel)
    {
        cameraMat = glm::translate(cameraMat, cameraTranslate);
        cameraMat = glm::translate(cameraMat, -cameraTranslate);
        cameraMat = glm::rotate(cameraMat, RAIDAN(rotation), vec3(0.0, 1.0, 0.0));
        cameraMat = glm::translate(cameraMat, cameraTranslate);

        animatedModel->animate(animation, animationStep);
        animatedModel->onUpdate();

        renderer->renderModel(animatedModel, cameraMat);
    }
}

GLvoid ThirdPersonCamera::Reset()
{
    animation = 0;
}

void ThirdPersonCamera::onKeyPress(int Key, int State)
{
    if (State == HOLDING || State == PRESSED)
    {
        GLfloat RotationRadians = RAIDAN(-rotation);

        switch (Key)
        {
        case W_KEY:
        {
            movement.x += GLfloat(sin(RotationRadians)) / 3;
            movement.z += GLfloat(cos(RotationRadians)) / 3;
            animationStep = 0.15f;
            animation = 1;
            break;
        }

        case S_KEY:
        {
            movement.x -= GLfloat(sin(RotationRadians)) / 3;
            movement.z -= GLfloat(cos(RotationRadians)) / 3;
            animationStep = 0.4f;
            animation = 7;
            break;
        }

        case A_KEY:
        {
            animationStep = 0.075f;
            animation = 1;
            break;
        }

        case D_KEY:
        {
            animationStep = 0.075f;
            animation = 1;
            break;
        }

        default: break;
        }
    }
}

void ThirdPersonCamera::onMotion(float pos_x, float pos_y)
{
    if (rotation >= 360)
    {
        rotation = 0;
    }

    if (rotation < 0)
    {
        rotation = 360;
    }

    if (pitch + pos_y < 60 && pitch + pos_y > -25)
    {
        pitch += GLfloat(pos_y);
    }

    rotation += GLfloat(pos_x);
}

GLfloat ThirdPersonCamera::getPitch()
{
    return pitch;
}

GLfloat ThirdPersonCamera::getRotation()
{
    return rotation;
}

vec3 ThirdPersonCamera::getTranslate()
{
    return cameraTranslate;
}

GLvoid ThirdPersonCamera::setPosition(vec3 vec)
{
    cameraTranslate = vec;
    movement = vec3(0.0);
}

GLvoid ThirdPersonCamera::setRotation(GLfloat value)
{
    rotation = value;
}

GLvoid ThirdPersonCamera::setPitch(GLfloat value)
{
    pitch = value;
}

void ThirdPersonCamera::initialise(RendererGL * world)
{
    renderer = world;
}

vec3 ThirdPersonCamera::getPosition()
{
    mat4 mat = glm::perspective(70.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    vec4 position = (mat * vec4(cameraTranslate + movement + movement, 1.0));

    return((vec3(-position.x, -position.y, -position.z)));
}

vec3 ThirdPersonCamera::getPosition(vec3 vec)
{
    mat4 mat = glm::perspective(70.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    vec4 position = (mat * vec4(cameraTranslate + vec + movement + movement, 1.0));

    return((vec3(-position.x, -position.y, -position.z)));
}