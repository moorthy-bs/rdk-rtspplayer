SUMMARY = "A RT Remote and Spark framework based RTSP stream player using GStreamer"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/moorthy-bs/rdk-rtspplayer.git;branch=main"
SRCREV = "${AUTOREV}"

DEPENDS += "glib-2.0 pxcore-libnode"
DEPENDS += "${@bb.utils.contains('DISTRO_FEATURES', 'gstreamer1', 'gstreamer1.0 gstreamer1.0-plugins-base', 'gstreamer gst-plugins-base', d)}"

S = "${WORKDIR}/git/"

inherit autotools pkgconfig coverity

FILES_${PN} = "${bindir}/rdkrtspplayer"
