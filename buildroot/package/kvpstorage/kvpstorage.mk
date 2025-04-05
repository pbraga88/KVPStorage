################################################################################
# kvpstorage.mk – Buildroot package for the kvpstorage application
################################################################################

KVPSTORAGE_SITE = $(TOPDIR)/package/kvpstorage
KVPSTORAGE_SITE_METHOD = local
KVPSTORAGE_SUPPORTS_IN_SOURCE_BUILD = NO


KVPSTORAGE_DEPENDENCIES = libsodium

KVPSTORAGE_LICENSE = MIT
# KVPSTORAGE_LICENSE_FILES = LICENSE

KVPSTORAGE_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
KVPSTORAGE_CONF_OPTS += -DCMAKE_TOOLCHAIN_FILE=$(HOST_DIR)/share/buildroot/toolchainfile.cmake

define KVPSTORAGE_CONFIGURE_CMDS
	(cd $(@D) && $(TARGET_CONFIGURE_OPTS) cmake $(KVPSTORAGE_CONF_OPTS) $(KVPSTORAGE_SITE))
endef


define KVPSTORAGE_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)
endef

define KVPSTORAGE_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/apps/cli/kvpstorage_cli $(TARGET_DIR)/usr/bin/kvpstorage
	$(INSTALL) -D -m 0644 $(KVPSTORAGE_SITE)/keys/kvpstorage.key \
	    $(TARGET_DIR)/etc/kvpstorage/keys/kvpstorage.key
	$(INSTALL) -D -m 0644 $(KVPSTORAGE_SITE)/keys/kvpstorage.hmac \
	    $(TARGET_DIR)/etc/kvpstorage/keys/kvpstorage.hmac
endef

$(eval $(generic-package))
