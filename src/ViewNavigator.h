#ifndef VIEW_NAVIGATOR_H
#define VIEW_NAVIGATOR_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class ViewNavigator
{
public:
    ViewNavigator();
    ViewNavigator(float distance, float angleX, float angleY, float angleZ=0.0f);
    
    void pan(int pixelX, int pixelY);
    void rotate(int pixelX, int pixelY);
    void zoom(float increment);
    void front();
    void left();
    void top();
    
    const glm::vec3& origin();
    const glm::vec3& position();
    const glm::quat& rotation();
    
    void setPivotPoint(const glm::vec3& point);
    void setDefaultDistance(float distance);
    void setStartPixel(int x, int y);
    void setRotationScale(float scale);
    
private:
    glm::vec3 m_pivot;
    glm::vec3 m_position;
    glm::quat m_orientation;
    
    float m_rotationScale;
    int m_pixelXPrev;
    int m_pixelYPrev;
};

#endif // VIEW_NAVIGATOR_H