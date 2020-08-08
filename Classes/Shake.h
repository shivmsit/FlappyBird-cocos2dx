#ifndef __SHAKE_H__
#define __SHAKE_H__

#include "cocos2d.h"

USING_NS_CC;

class Shake : public ActionInterval
{
public:
    /*
     * Create a shake action with duration and magnitude
     */
    static Shake* create(float duration, float magnitude);
    static Shake* create(float duration, Vec2 magnitude);

    /*
     * Overrides
     */
    virtual Shake* clone() const override;
    virtual Shake* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual void stop(void) override;

    bool initWithDuration(float duration, cocos2d::Vec2 magnitude);

CC_CONSTRUCTOR_ACCESS:
    Shake() { }
    virtual ~Shake() { }

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Shake);

private:
    Vec2 _magnitude;
    Vec2 _initial;
};

#endif //__SHAKE_H__
