
FUNCTION json2bson : UDINT (*Return is the BSON size*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		Bin : UDINT; (*BSON output*)
		Str : UDINT; (*JSON to convert*)
		BufferSize : UDINT; (*Size of Buffer for BSON output*)
	END_VAR
END_FUNCTION
