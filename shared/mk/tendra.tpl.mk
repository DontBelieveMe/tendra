# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_TPL_MK_)
_TENDRA_WORK_TPL_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(TPLSRCS)
.BEGIN:
	@${ECHO} '$${TPLSRCS} must be set'
	@${EXIT} 1;
.endif

# TODO: assert TPLSRCS may not contain ../


CAPSULES+=	${TPLSRCS:S/.tpl/.j/:C/^/${OBJ_SDIR}\//}

.for src in ${TPLSRCS}
${OBJ_SDIR}/${src:S/.tpl/.j/}: ${src}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${src}"
	${TPL} ${TPLOPTS} ${.ALLSRC} ${.TARGET}
.endfor



#
# User-facing targets
#

all:: ${CAPSULES}


clean::
	${RMFILE} ${CAPSULES}


install::



.endif	# !defined(_TENDRA_WORK_TPL_MK_)
