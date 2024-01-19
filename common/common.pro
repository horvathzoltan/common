TEMPLATE = subdirs

SUBDIRS += \
    coreappworker \
    helpers \
    macrofactory \
    shortguid \
    logger \

logger.depends = shortguid macrofactory
helpers.depends = logger macrofactory shortguid

