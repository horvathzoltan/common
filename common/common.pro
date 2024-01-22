TEMPLATE = subdirs

SUBDIRS += \
    workers \
    helpers \
    macros \
    nameof \
    shortguid \
    logger \
    exceptions \

logger.depends = shortguid macros
helpers.depends = logger macros shortguid

