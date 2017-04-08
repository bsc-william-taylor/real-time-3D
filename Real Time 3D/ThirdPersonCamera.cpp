
#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera()
{
	m_CameraTranslate = vec3(0.0, -2.0, 0.0);
	m_CameraSpeed = vec3();
	m_AnimationStep = 0;
	m_Animation = 0;
	m_Rotation = 0.0f;
	m_Pitch = 0.0f;
	m_Y = 0.0f;

	m_Model = NULL;
}

ThirdPersonCamera::~ThirdPersonCamera()
{

}

GLvoid ThirdPersonCamera::setPlayerModel(DynamicModel * m)
{
	m_Model = m;
}

GLvoid ThirdPersonCamera::CancelMovement()
{
	m_Movement = vec3(0, 0, 0);
}

void ThirdPersonCamera::Update()
{
	m_CameraTranslate += m_Movement;

	m_Model->getMatrix()->RotateView(RAIDAN(m_Pitch), vec3(1.0, 0.0, 0.0));
	m_Model->getMatrix()->TranslateView(m_Movement + vec3(0.0, -1.5, -3.0));

	m_pWorld->TranslateView(m_CameraTranslate);
	m_pWorld->TranslateView(-m_CameraTranslate);
	m_pWorld->RotateView(RAIDAN(m_Pitch), vec3(1.0, 0.0, 0.0));
	m_pWorld->RotateView(RAIDAN(m_Rotation), vec3(0.0, 1.0, 0.0));
	m_pWorld->TranslateView(m_CameraTranslate);

	CancelMovement();

	m_Model->Animate(m_Animation, m_AnimationStep);
	m_Model->Update();

	m_pWorld->RenderModel(m_Model);
}

GLvoid ThirdPersonCamera::Reset()
{
	m_Animation = 0;
}

void ThirdPersonCamera::KeyPress(int Key, int State)
{
	if(State == HOLDING || State == PRESSED)
	{
		GLfloat RotationRadians = RAIDAN(-m_Rotation);
		switch(Key) 
		{
			case W_KEY:
			{
				m_Movement.x += GLfloat(sin(RotationRadians)) / 3;
				m_Movement.z += GLfloat(cos(RotationRadians)) / 3;
				m_AnimationStep = 0.075f;
				m_Animation = 1;
				break;
			}

			case S_KEY:
			{
				m_Movement.x -= GLfloat(sin(RotationRadians)) / 3;
				m_Movement.z -= GLfloat(cos(RotationRadians)) / 3;
				m_AnimationStep = 0.25f;
				m_Animation = 7;
				break;
			}

			case A_KEY:
			{
				m_AnimationStep = 0.075f;
				m_Animation = 1;
				break;
			}

			case D_KEY:
			{
				m_AnimationStep = 0.075f;
				m_Animation = 1;
				break;
			}

			default: break;
		}
	}
}

void ThirdPersonCamera::Motion(float pos_x, float pos_y)
{
	if(m_Rotation >= 360) 
	{
		m_Rotation = 0;
	}

	if(m_Rotation < 0) 
	{
		m_Rotation = 360;
	}

	m_Rotation += GLfloat(pos_x);
	m_Pitch += GLfloat(pos_y);
}

// get & set functions
GLfloat ThirdPersonCamera::getPitch()
{ 
	return m_Pitch; 
}

GLfloat ThirdPersonCamera::getRotation()
{ 
	return m_Rotation; 
}

vec3 ThirdPersonCamera::getTranslate()
{
	return m_CameraTranslate;
}

GLvoid ThirdPersonCamera::setPosition(vec3 vec)
{
	m_CameraTranslate = vec;
	m_Movement = vec3(0.0); 
}

GLvoid ThirdPersonCamera::setRotation(GLfloat rotation)
{
	m_Rotation = rotation;
}

GLvoid ThirdPersonCamera::setPitch(GLfloat pitch)
{
	m_Pitch = pitch;
}

void ThirdPersonCamera::Initialise(GL_Renderer * world)
{
	m_pWorld = world;
}

vec3 ThirdPersonCamera::getPosition()
{
	mat4 mat = glm::perspective(70.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	vec4 position = (mat * vec4(m_CameraTranslate + m_Movement + m_Movement, 1.0));

	return((vec3(-position.x, -position.y, -position.z)));
}

vec3 ThirdPersonCamera::getPosition(vec3 vec)
{
	mat4 mat = glm::perspective(70.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	vec4 position = (mat * vec4(m_CameraTranslate + vec + m_Movement + m_Movement, 1.0));

	return((vec3(-position.x, -position.y, -position.z)));
}