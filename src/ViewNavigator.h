//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

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
	float m_translationScale;
    int m_pixelXPrev;
    int m_pixelYPrev;
};

#endif // VIEW_NAVIGATOR_H