ENCODER_ENABLE = yes

# Per-unit build switch. The simityl fleet is not uniform: most units carry a
# PMW3389 with a 4-pulse/detent encoder, but at least one has a PMW3360 with a
# 2-pulse encoder. Select with:
#
#   qmk compile -kb simityl -km simian                        # 3389 + 4-pulse
#   qmk compile -kb simityl -km simian -e SIMITYL_UNIT=3360   # 3360 + 2-pulse
#
# The wrong pointing driver fails the sensor signature check and leaves the
# pointer silently dead. The wrong encoder resolution is less dramatic: too
# high and it scrolls every other detent, too low and it scrolls twice per
# detent. If a unit ever turns up as a 3360 with a 4-pulse encoder (or the
# reverse), split this into two variables rather than adding a third case.
SIMITYL_UNIT ?= 3389

ifeq ($(strip $(SIMITYL_UNIT)), 3360)
    POINTING_DEVICE_DRIVER = pmw3360
    OPT_DEFS += -DENCODER_RESOLUTION=2
else ifeq ($(strip $(SIMITYL_UNIT)), 3389)
    POINTING_DEVICE_DRIVER = pmw3389
else
    $(error SIMITYL_UNIT must be 3389 or 3360, got '$(SIMITYL_UNIT)')
endif
