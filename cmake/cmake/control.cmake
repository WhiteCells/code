set(VAR1 "0")

set(VAR2 1x)

if (VAR1)
    message("===")
elseif (VAR2 GREATER_EQUAL 0)
    message("+++")
elseif (VAR2 LESS_EQUAL 3)
    message("***")
elseif (VAR2 EQUAL "1x")
    message("xxx")
else ()
    message("---")
endif ()