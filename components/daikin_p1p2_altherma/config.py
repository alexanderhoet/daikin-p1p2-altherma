import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome import pins

CONF_RX_PIN = "rx_pin"
CONF_TX_PIN = "tx_pin"
CONF_RST_PIN = "rst_pin"

daikin_p1p2_altherma_ns = cg.esphome_ns.namespace("daikin_p1p2_altherma")
DaikinP1P2Altherma = daikin_p1p2_altherma_ns.class_("DaikinP1P2Altherma", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DaikinP1P2Altherma),
        cv.Required(CONF_RX_PIN): pins.gpio_input_pin_schema,
        cv.Required(CONF_TX_PIN): pins.gpio_output_pin_schema,
        cv.Required(CONF_RST_PIN): pins.gpio_output_pin_schema,
    }
)

async def to_code(config):
    cg.add_platformio_option(
        "lib_deps",
        "alexanderhoet/esp32-daikin-p1p2-serial"
    )

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    rx = await cg.gpio_pin_expression(config[CONF_RX_PIN])
    tx = await cg.gpio_pin_expression(config[CONF_TX_PIN])
    rst = await cg.gpio_pin_expression(config[CONF_RST_PIN])

    cg.add(var.set_rx_pin(rx))
    cg.add(var.set_tx_pin(tx))
    cg.add(var.set_rst_pin(rst))