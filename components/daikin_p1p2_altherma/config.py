import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

daikin_p1p2_altherma_ns = cg.esphome_ns.namespace("daikin_p1p2_altherma")
DaikinP1P2Altherma = daikin_p1p2_altherma_ns.class_(
    "DaikinP1P2Altherma", cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DaikinP1P2Altherma),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)