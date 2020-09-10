  
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_POWER, CONF_ANALOG, CONF_DELAY, ICON_FLASH, UNIT_VOLT, CONF_ID
from . import  ADCPLEXComponent


def validate_adc_pin(value):
    vcc = str(value).upper()
    if vcc == 'VCC':
        return cv.only_on_esp8266(vcc)
    return pins.analog_pin(value)

DEPENDENCIES = ['ADCPLEX']

ADCPLEXSensor = ADCPLEX_ns.class_('ADCPLEXSensor', sensor.ADCSensor)

CONF_ADCPLEX_ID = 'ADCPLEX_id'
CONFIG_SCHEMA = sensor.sensor_schema(UNIT_VOLT, ICON_FLASH, 3).extend({
    cv.GenerateID(): cv.declare_id(ADCPLEXSensor),
    cv.GenerateID(CONF_ADCPLEX_ID): cv.use_id(ADCPLEXComponent),
    cv.Required(CONF_POWER): pins.output_pin,
    cv.Required(CONF_ANALOG): validate_adc_pin,
    cv.Optional(CONF_DELAY, default=100): cv.integer,
}).extend(cv.polling_component_schema('60s'))


def to_code(config):
    paren = yield cg.get_variable(config[CONF_ADCPLEX_ID])
    var = cg.new_Pvariable(config[CONF_ID], paren)
    yield sensor.register_sensor(var, config)
    yield cg.register_component(var, config)

    cg.add(var.set_power_pin(config[CONF_POWER]))
    cg.add(var.set_delay(config[CONF_DELAY]))
    cg.add(var.set_pin(config[CONF_ANALOG]))

    cg.add(paren.register_sensor(var))