kritarcdir = $(kde_datadir)/krita/kritadeskewfilter.desktop

kde_services_DATA = kritaLineSampler.desktop


INCLUDES  =  -I$(srcdir)/../../../sdk \
	-I$(srcdir)/../../../core \
	-I$(srcdir)/../../../kritacolor/ \
	-I$(srcdir)/../../../ui \
	$(KOFFICE_INCLUDES) \
	$(all_includes)

# Allow exceptions for this plugin so gmm compiles ok
# KDE_CXXFLAGS = $(USE_EXCEPTIONS)

kde_module_LTLIBRARIES = kritadeskewfilter.la

kritadeskewfilter_la_SOURCES = kis_deskew_filter_plugin.cc \
	kis_deskew_filter.cc bitutil.cc bwimage.cc deskewer.cc \
	kritafact.cc

noinst_HEADERS = kis_deskew_filter_plugin.h \
	kis_deskew_filter.h bitutil.h \
	bwfactory.h bwfactory.h deskewer.h kritafact.h

kritadeskewfilter_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)
kritadeskewfilter_la_LIBADD =  -lkritacommon

kritadeskewfilter_la_METASOURCES = AUTO
