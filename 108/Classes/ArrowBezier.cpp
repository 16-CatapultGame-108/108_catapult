//
//  ArrowBezier.cpp
//  demo
//
//  Created by apple on 16/7/8.
//
//

#include "ArrowBezier.h"

static inline float bezierat1( float a, float b, float d, float t )
{
    return (powf(1-t,2) * a +
            2.0f*t*(1-t)*b +
            powf(t,2)*d );
}

ArrowBezier::ArrowBezier() {}

ArrowBezier* ArrowBezier::create(float t, const ccQuadBezierConfig& c) {
    ArrowBezier *pBezierBy = new (std::nothrow) ArrowBezier();
    pBezierBy->initWithDuration(t, c);
    pBezierBy->autorelease();
    
    return pBezierBy;
}

bool ArrowBezier::initWithDuration(float t, const ccQuadBezierConfig& c)
{
    bool bRet = false;
    
    if (CCActionInterval::initWithDuration(t))
    {
        _config = c;
        return true;
    }
    
    return bRet;
}

void ArrowBezier::update(float time)
{
    if (_target) {
        float xa = 0;
        float xb = _config.controlPoint.x;
        float xd = _config.endPosition.x;
        
        float ya = 0;
        float yb = _config.controlPoint.y;
        float yd = _config.endPosition.y;
        
        float x = bezierat1(xa, xb, xd, time);
        float y = bezierat1(ya, yb, yd, time);
        
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();
        Vec2 diff = currentPos - _previousPosition;
        _startPosition = _startPosition + diff;
        
        Vec2 newPos = _startPosition + Vec2(x,y);
        _target->setPosition(newPos);
        
        _previousPosition = newPos;
        
        if (0 != time) {
            Vec2 vector = currentPos - newPos;
            float radians = vector.getAngle();
            float degrees = CC_RADIANS_TO_DEGREES(-1 * radians);
            _target->setRotation(degrees - 180);
        }
        
#else
        _target->setPosition( _startPosition + Vec2(x,y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
        
    }
}