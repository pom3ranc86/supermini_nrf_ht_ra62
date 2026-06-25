#pragma once

#include "RegionMap.h"
#include <string.h>

#ifdef MESHCORE_CZ_REGION_PRESET

static inline void bootstrapCzRegions(RegionMap& map) {
  // Preferred scope: *, cz — forward unscoped messages and cz-scoped only.
  // Optional build flag MESHCORE_CZ_SUBREGION="cz-ulk" adds that county (e.g. *, cz, cz-ulk).
  map.getWildcard().flags = 0;

  RegionEntry* cz = map.putRegion("cz", 0);
  if (!cz) return;
  cz->flags = 0;

  static const char* counties[] = {
    "cz-pha", "cz-stc", "cz-jhc", "cz-plz", "cz-kvk", "cz-ulk", "cz-lbk",
    "cz-hkk", "cz-pak", "cz-vys", "cz-jmk", "cz-olk", "cz-zlk", "cz-msk",
  };
  for (unsigned i = 0; i < sizeof(counties) / sizeof(counties[0]); i++) {
    RegionEntry* r = map.putRegion(counties[i], cz->id);
    if (r) r->flags = REGION_DENY_FLOOD;
  }

#ifdef MESHCORE_CZ_SUBREGION
  RegionEntry* sub = map.findByName(MESHCORE_CZ_SUBREGION);
  if (sub) {
    sub->flags = 0;
    map.setHomeRegion(sub);
  }
#endif

  map.setDefaultRegion(cz);
}

#endif
