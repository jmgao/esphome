import voluptuous as vol

import esphome.config_validation as cv
from esphome.const import CONF_COMPONENTS, CONF_ID, CONF_LAMBDA
from esphome.cpp_generator import Pvariable, process_lambda, variable
from esphome.cpp_helpers import register_component
from esphome.cpp_types import Component, ComponentPtr, esphome_ns, std_vector

CustomComponentConstructor = esphome_ns.class_('CustomComponentConstructor')
MULTI_CONF = True

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(CustomComponentConstructor),
    vol.Required(CONF_LAMBDA): cv.lambda_,
    vol.Optional(CONF_COMPONENTS): cv.ensure_list(cv.Schema({
        cv.GenerateID(): cv.declare_variable_id(Component)
    }).extend(cv.COMPONENT_SCHEMA)),
})


def to_code(config):
    template_ = yield process_lambda(config[CONF_LAMBDA], [],
                                     return_type=std_vector.template(ComponentPtr))

    rhs = CustomComponentConstructor(template_)
    custom = variable(config[CONF_ID], rhs)
    for i, comp_config in enumerate(config.get(CONF_COMPONENTS, [])):
        comp = Pvariable(comp_config[CONF_ID], custom.get_component(i))
        register_component(comp, comp_config)


BUILD_FLAGS = '-DUSE_CUSTOM_COMPONENT'