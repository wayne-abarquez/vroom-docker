/*

This file is part of VROOM.

Copyright (c) 2015-2020, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include <numeric>

#include "structures/vroom/job.h"
#include "utils/exception.h"

namespace vroom {

inline Duration get_tw_length(const std::vector<TimeWindow>& tws) {
  return std::accumulate(std::next(tws.begin()),
                         tws.end(),
                         tws[0].length,
                         [](auto sum, auto tw) { return sum + tw.length; });
}

Job::Job(Id id,
         const Location& location,
         Duration service,
         const Amount& delivery,
         const Amount& pickup,
         const Skills& skills,
         Priority priority,
         const std::vector<TimeWindow>& tws)
  : location(location),
    id(id),
    type(JOB_TYPE::SINGLE),
    service(service),
    delivery(delivery),
    pickup(pickup),
    skills(skills),
    priority(priority),
    tws(tws),
    tw_length(get_tw_length(tws)) {
  check_tws();
}

Job::Job(Id id,
         JOB_TYPE type,
         const Location& location,
         Duration service,
         const Amount& amount,
         const Skills& skills,
         Priority priority,
         const std::vector<TimeWindow>& tws)
  : location(location),
    id(id),
    type(type),
    service(service),
    delivery((type == JOB_TYPE::DELIVERY) ? amount : Amount(amount.size())),
    pickup((type == JOB_TYPE::PICKUP) ? amount : Amount(amount.size())),
    skills(skills),
    priority(priority),
    tws(tws),
    tw_length(get_tw_length(tws)) {
  assert(type == JOB_TYPE::PICKUP or type == JOB_TYPE::DELIVERY);
  check_tws();
}

bool Job::is_valid_start(Duration time) const {
  bool valid = false;

  for (const auto& tw : tws) {
    if (tw.contains(time)) {
      valid = true;
      break;
    }
  }

  return valid;
}

void Job::check_tws() const {
  if (tws.size() == 0) {
    throw Exception(ERROR::INPUT,
                    "Empty time-windows for job " + std::to_string(id) + ".");
  }

  if (tws.size() > 1) {
    for (std::size_t i = 0; i < tws.size() - 1; ++i) {
      if (tws[i + 1].start <= tws[i].end) {
        throw Exception(ERROR::INPUT,
                        "Unsorted or overlapping time-windows for job " +
                          std::to_string(id) + ".");
      }
    }
  }
}

} // namespace vroom
