//
//  ArrowBezier.h
//  demo
//
//  Created by apple on 16/7/8.
//
//

#ifndef ArrowBezier_h
#define ArrowBezier_h
#include <iostream>

#include "cocos2d.h"
USING_NS_CC;


typedef struct _ccQuadBezierConfig {
    Point endPosition;
    Point controlPoint;
} ccQuadBezierConfig;

class ArrowBezier: public BezierBy
{
public:
    ArrowBezier();
    static ArrowBezier* create(float t, const ccQuadBezierConfig& c);
    bool initWithDuration(float t, const ccQuadBezierConfig& c);
    virtual void update(float time);
    
private:
    ccQuadBezierConfig _config;
};

#endif /* ArrowBezier_h */
