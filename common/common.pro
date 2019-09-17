TEMPLATE = subdirs

SUBDIRS += \
    helper \
    macrofactory \
    shortguid \
    logger \

logger.depends = shortguid macrofactory
helper.depends = logger macrofactory shortguid

