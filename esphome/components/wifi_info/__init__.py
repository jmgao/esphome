from esphome.components import text_sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_BSSID, CONF_ID, CONF_IP_ADDRESS, CONF_NAME, CONF_SSID
from esphome.core import coroutine

DEPENDENCIES = ['wifi']

wifi_info_ns = cg.esphome_ns.namespace('wifi_info')
IPAddressWiFiInfo = wifi_info_ns.class_('IPAddressWiFiInfo', text_sensor.TextSensor, cg.Component)
SSIDWiFiInfo = wifi_info_ns.class_('SSIDWiFiInfo', text_sensor.TextSensor, cg.Component)
BSSIDWiFiInfo = wifi_info_ns.class_('BSSIDWiFiInfo', text_sensor.TextSensor, cg.Component)

PLATFORM_SCHEMA = text_sensor.PLATFORM_SCHEMA.extend({
    cv.Optional(CONF_IP_ADDRESS): cv.nameable(text_sensor.TEXT_SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(IPAddressWiFiInfo),
    })),
    cv.Optional(CONF_SSID): cv.nameable(text_sensor.TEXT_SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(SSIDWiFiInfo),
    })),
    cv.Optional(CONF_BSSID): cv.nameable(text_sensor.TEXT_SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(BSSIDWiFiInfo),
    })),
})


@coroutine
def setup_conf(config, key):
    if key in config:
        conf = config[key]
        var = cg.new_Pvariable(conf[CONF_ID], conf[CONF_NAME])
        yield cg.register_component(var, conf)
        yield text_sensor.register_text_sensor(var, conf)


def to_code(config):
    yield setup_conf(config, CONF_IP_ADDRESS)
    yield setup_conf(config, CONF_SSID)
    yield setup_conf(config, CONF_BSSID)
