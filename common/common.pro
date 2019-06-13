TEMPLATE = subdirs

SUBDIRS += \
    helper \
    macrofactory \
    shortguid \
    logger \

logger.depends = macrofactory shortguid
helper.depends = logger macrofactory shortguid
