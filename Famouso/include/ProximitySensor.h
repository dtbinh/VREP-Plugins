#pragma once

#include <VREPSensor.h>

#include <BaseEvent.h>
#include <Serializer.h>

#include <atomic>

struct ProximityConfig{
  struct EventConfig : public BaseConfig{
    using TimeValueType = Value<float, 1, false>;
    using PositionValueType = Value<float, 3, false>;
  };
  
  using Vector1f  = Value<float, 1, false>;
  using Vector3f  = Value<float, 3, false>;
  using Vector2fu = Value<float, 2, false>;
  using Int       = Value<int, 1, false>;
  using ReferenceAttribute   = Attribute<id::attribute::Reference, Int, Dimensionless>;
  using OrientationAttribute = Attribute<id::attribute::Orientation, Vector3f, Radian>;
  using DistanceAttribute    = Attribute<id::attribute::Distance, Vector1f, Meter>;
  using AngleAttribute  = Attribute<id::attribute::Angle, Vector2fu, Radian, std::ratio<180000,(long)(M_PI*1000)>>;
  using ReferenceEvent   = typename BaseEvent<EventConfig>::append<ReferenceAttribute>::type;
  using OrientationEvent = typename ReferenceEvent::append<OrientationAttribute>::type;
  using PolarAngleEvent  = typename OrientationEvent::append<AngleAttribute>::type;
  using DistanceEvent    = typename PolarAngleEvent::append<DistanceAttribute>::type;
};

class ProximitySensor : public VREPSensor<ProximityConfig::DistanceEvent>{
  private:
    using Base =  VREPSensor<ProximityConfig::DistanceEvent>;

  protected:
    void print(std::ostream& out) const;

  public:
    using Subject = typename Base::Subject;

    ProximitySensor(simInt id, const Subject& subject) : Base(id, subject){};

    ProximitySensor& operator=(const ProximitySensor&) = delete;
    virtual void update();
};
