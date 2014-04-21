#include "ViewNavigator.h"

#include <glm/gtc/matrix_transform.hpp>

ViewNavigator::ViewNavigator()
    :m_pixelXPrev(0), m_pixelYPrev(0), m_rotationScale(0.5f)
{
}

ViewNavigator::ViewNavigator(float distance, float angleX, float angleY, float angleZ)
    : m_position(0.0, 0.0, -distance), m_pixelXPrev(0), m_pixelYPrev(0), m_rotationScale(0.5f), m_translationScale(0.005f)
{
	m_orientation = glm::angleAxis(-angleX, glm::vec3(1.0, 0.0, 0.0));
	m_orientation = glm::angleAxis(-angleY, glm::vec3(0.0, 1.0, 0.0)) * m_orientation;
}
    
void ViewNavigator::pan(int pixelX, int pixelY)
{
	float dX = (pixelX - m_pixelXPrev);
	float dY = (pixelY - m_pixelYPrev);

	m_pixelXPrev = pixelX;
	m_pixelYPrev = pixelY;

	m_pivot.x += dX * m_translationScale;
	m_pivot.y += -dY * m_translationScale;
}

void ViewNavigator::rotate(int pixelX, int pixelY)
{
    //use the distance as an angle
    float angleX = (pixelY - m_pixelYPrev) * m_rotationScale;
    float angleY = (pixelX - m_pixelXPrev) * m_rotationScale;
    
    m_pixelXPrev = pixelX;
    m_pixelYPrev = pixelY;

	m_orientation = m_orientation * glm::angleAxis(angleY, glm::vec3(0.0, 1.0, 0.0));
	m_orientation = glm::angleAxis(angleX, glm::vec3(1.0, 0.0, 0.0)) * m_orientation;
}

void ViewNavigator::zoom(float increment)
{
    m_position += glm::vec3(0.0, 0.0, -increment);
}

void ViewNavigator::front()
{

}

void ViewNavigator::left()
{

}
void ViewNavigator::top()
{

}

const glm::vec3& ViewNavigator::origin() 
{
    return m_pivot;
}

const glm::vec3& ViewNavigator::position() 
{
    return m_position;
}

const glm::quat& ViewNavigator::rotation() 
{
    return m_orientation;
}

void ViewNavigator::setPivotPoint(const glm::vec3& point)
{
    m_pivot = point;
}

void ViewNavigator::setDefaultDistance(float distance)
{
	m_position[2] = -distance;
}

void ViewNavigator::setStartPixel(int x, int y)
{
    m_pixelXPrev = x;
    m_pixelYPrev = y;
}

void ViewNavigator::setRotationScale(float scale)
{
    m_rotationScale = scale;
}
    
    