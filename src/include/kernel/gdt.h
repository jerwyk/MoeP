#pragma once

#include <com/types.h>

namespace MoeP
{
    namespace kernel
    {
        class GlobalDescriptorTable
        {
            public:
            /*
            Structure of GDT:
            ---------------------------------------------------------------------------------------------------------
            |base_vhi(8bits)|flags(4bits)|limit(4bits)|type(8bits)|base_hi(8bits)|base_lo(16bits)|limit_lo(16bits)|
            ---------------------------------------------------------------------------------------------------------
            */
            class SegmentDescriptor
            {
                private:
                uint16 limit_lo;
                uint16 base_lo;
                uint8 base_hi;
                uint8 type;
                uint8 flag_limit_hi;
                uint8 base_vhi;
                public:
                SegmentDescriptor(uint32 base, uint32 limit, uint8 type);
                uint32 Limit();
                uint32 Base();
            }__attribute__((packed));

            struct GDTPointer
            {
                uint16 limit;               // The upper 16 bits of all selector limits.
                uint32 base;                
            }__attribute__((packed));

            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            uint16 CodeSegmentSelector();
            uint16 DataSegmentSelector();

        };
    }
}