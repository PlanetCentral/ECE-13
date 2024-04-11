	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 3
	.globl	_BOARD_Init                     ; -- Begin function BOARD_Init
	.p2align	2
_BOARD_Init:                            ; @BOARD_Init
	.cfi_startproc
; %bb.0:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_BOARD_End                      ; -- Begin function BOARD_End
	.p2align	2
_BOARD_End:                             ; @BOARD_End
	.cfi_startproc
; %bb.0:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_BOARD_GetPBClock               ; -- Begin function BOARD_GetPBClock
	.p2align	2
_BOARD_GetPBClock:                      ; @BOARD_GetPBClock
	.cfi_startproc
; %bb.0:
	mov	w0, #11520
	movk	w0, #305, lsl #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_BOARD_GetSysClock              ; -- Begin function BOARD_GetSysClock
	.p2align	2
_BOARD_GetSysClock:                     ; @BOARD_GetSysClock
	.cfi_startproc
; %bb.0:
	mov	w0, #46080
	movk	w0, #1220, lsl #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_SERIAL_Init                    ; -- Begin function SERIAL_Init
	.p2align	2
_SERIAL_Init:                           ; @SERIAL_Init
	.cfi_startproc
; %bb.0:
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
