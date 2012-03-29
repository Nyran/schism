
// Copyright (c) 2012 Christopher Lux <christopherlux@gmail.com>
// Distributed under the Modified BSD License, see license.txt.

#ifndef SCM_CORE_TIME_ACCUM_TIMER_BASE_H_INCLUDED
#define SCM_CORE_TIME_ACCUM_TIMER_BASE_H_INCLUDED

#include <scm/core/time/timer_base.h>

#include <scm/core/platform/platform.h>

namespace scm {
namespace time {

class __scm_export(core) accum_timer_base
{
public:
    typedef timer_base::nanosec_type    nanosec_type;

public:
    accum_timer_base();
    virtual ~accum_timer_base();

    virtual void                    stop()          = 0;
    virtual void                    collect()       = 0;
    virtual void                    force_collect() = 0;
    virtual void                    reset();

    nanosec_type                    last_time() const;
    nanosec_type                    accumulated_time() const;
    unsigned                        accumulation_count() const;
    nanosec_type                    average_time() const;

    double                          last_time(timer_base::time_unit tu) const;
    double                          accumulated_time(timer_base::time_unit tu) const;
    double                          average_time(timer_base::time_unit tu) const;

    virtual void                    report(std::ostream&               os,
                                           timer_base::time_unit       tunit  = timer_base::msec,
                                           size_t                      dsize  = 0,
                                           timer_base::throughput_unit tpunit = timer_base::MiBps) const = 0;
    virtual void                    detailed_report(std::ostream&               os,
                                                    timer_base::time_unit       tunit  = timer_base::msec,
                                                    size_t                      dsize  = 0,
                                                    timer_base::throughput_unit tpunit = timer_base::MiBps) const = 0;

protected:
    nanosec_type                    _last_time;
    nanosec_type                    _accumulated_time;
    unsigned                        _accumulation_count;

}; // class accum_timer_base

} // namespace time
} // namespace scm

#endif // SCM_CORE_TIME_ACCUM_TIMER_BASE_H_INCLUDED