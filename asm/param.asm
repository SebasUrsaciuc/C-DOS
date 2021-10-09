bpb_BytesPerSect:       dw 512
bpb_SectsPerCluster:    db 1
bpb_ReservedSects:      dw 1
bpb_FATsAmount:         db 2
bpb_MaxRootDirs:        dw 224
bpb_SectsAmount:        dw 2880
bpb_MediaType:          db 0xF0
bpb_SectsPerFat:        dw 9
bpb_SectsPerTrack:      dw 18
bpb_HeadsAmount:        dw 2
bpb_HiddenSects:        dd 0
bpb_SectsAmount_Big:    dd 0
bpb_DrvNum:             db 0
bpb_Flags:              db 0
bpb_ExtBPBType:         db 0x29
bpb_VolId:              dd 0
bpb_VolLabel:           db "C-DOS Drive"
bpb_FileSys:            db "FAT12   "