
#include "FreeCamera.h"

FreeCamera::FreeCamera()
{
	m_CameraTranslate = vec3();
	m_CameraSpeed = vec3();
	m_Rotation = 0.0f;
	m_Pitch = 0.0f;
}

FreeCamera::~FreeCamera()
{

}


GLvoid FreeCamera::CancelMovement()
{
	m_Movement = vec3(0, 0, 0);
}

void FreeCamera::Update()
{
	m_CameraTranslate += m_Movement;
	
	m_pWorld->TranslateView(m_CameraTranslate);

	m_pWorld->TranslateView(-m_CameraTranslate);
	m_pWorld->RotateView(RAIDAN(m_Pitch), vec3(1.0, 0.0, 0.0));
	m_pWorld->RotateView(RAIDAN(m_Rotation), vec3(0.0, 1.0, 0.0));
	m_pWorld->TranslateView(m_CameraTranslate);

	CancelMovement();
}

void FreeCamera::KeyPress(int Key, int State)
{
	if(State == HOLDING || State == PRESSED)
	{
		GLfloat RotationRadians = RAIDAN(-m_Rotation);
		switch(Key) 
		{
			case W_KEY:
			{
				m_Movement.y -= GLfloat(sin(RAIDAN(-m_Pitch))) / 1;
				m_Movement.x += GLfloat(sin(RotationRadians)) / 2;
				m_Movement.z += GLfloat(cos(RotationRadians)) / 2;
				break;
			}

			case S_KEY:
			{
				m_Movement.y += GLfloat(sin(RAIDAN(-m_Pitch))) / 1;
				m_Movement.x -= GLfloat(sin(RotationRadians)) / 2;
				m_Movement.z -= GLfloat(cos(RotationRadians)) / 2;
				break;
			}

			case A_KEY:
			{
				m_Movement.x += GLfloat(cos(RotationRadians)) / 2;
				m_Movement.z -= GLfloat(sin(RotationRadians)) / 2;
				break;
			}

			case D_KEY:
			{
				m_Movement.x -= GLfloat(cos(RotationRadians)) / 2;
				m_Movement.z += GLfloat(sin(RotationRadians)) / 2;
				break;
			}

			default: break;
		}
	}
}

void FreeCamera::Motion(float pos_x, float pos_y)
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
GLfloat FreeCamera::getPitch()
{ 
	return m_Pitch; 
}

GLfloat FreeCamera::getRotation()
{ 
	return m_Rotation; 
}

vec3 FreeCamera::getTranslate()
{
	return m_CameraTranslate;
}

GLvoid FreeCamera::setPosition(vec3 vec)
{
	m_CameraTranslate = vec;
	m_Movement = vec3(0.0); 
}

GLvoid FreeCamera::setRotation(GLfloat rotation)
{
	m_Rotation = rotation;
}

GLvoid FreeCamera::setPitch(GLfloat pitch)
{
	m_Pitch = pitch;
}

void FreeCamera::Initialise(GL_Renderer * world)
{
	m_pWorld = world;
}

vec3 FreeCamera::getPosition()
{
	mat4 mat = glm::perspective(70.0f, 16.0f/9.0f, 0.1f, 1000.0f);
	vec4 position = (mat * vec4((m_CameraTranslate + m_Movement + m_Movement), 1.0));
	return((vec3(-position.x, -position.y, -position.z)));
}
