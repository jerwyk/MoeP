#include <kernel/gdt.h>

GlobalDescriptorTable::GlobalDescriptorTable():
nullSegmentSelector(0, 0, 0), 
unusedSegmentSelector(0, 0, 0),
codeSegmentSelector(0, 64*1024*1024, 0x9A),
dataSegmentSelector(0, 64*1024*1024, 0x92)
{
    //this works now, but i dont quite understand why do u need +2
    //uint32 i[2];
    //i[1] = (uint32)this;
    //high byte of the size of the gdt
    //i[0] = sizeof(GlobalDescriptorTable) << 16;
    //tell the processor to use this table
    //asm volatile("lgdt (%0)": :"p" (((uint8*)i)+2));

    //uses a struct to load the gdt
    GDTPointer gdt;
    //lowbyte is the base of the gdt
    gdt.base = (uint32)this;
    //high byte of the size of the gdt
    gdt.limit = sizeof(GlobalDescriptorTable);
    //tell the processor to use this table
    asm volatile("lgdt %0" : : "m" (gdt));
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{

}

uint16 GlobalDescriptorTable::DataSegmentSelector()
{
    return (uint8*)&dataSegmentSelector - (uint8*)this;
}

uint16 GlobalDescriptorTable::CodeSegmentSelector()
{
    return (uint8*)&codeSegmentSelector - (uint8*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32 base, uint32 limit, uint8 type)
{
    uint8* target = (uint8*)this;

    if(limit <= 65536)
    {
        target[6] = 0x40;
    }
    else
    {
        //if the limit exceeds 20 bits, we use the least 12 bit as virtual bits if they are all 1
        if ((limit & 0xFFF) != 0xFFF) 
        {
            //work around if they are not all 1
            limit = (limit >> 12) - 1;
        }
        else
        {
            //if they are all 1, right shift by 12 to ignore the lower 12 bits
            limit = limit >> 12;
        }
        target[6] = 0xC0;
    }
    //set the limit part of the GDT
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    //set the base pointer part of the GDT
    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    //set access rights
    target[5] = type;
}

//return the limit in integer from the GDT structure
uint32 GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    if((flag_limit_hi & 0xC0) == 0xC0)
    {
        return ((flag_limit_hi & 0xF) << 28) + (limit_lo << 12) +  0xFFF;
    }
    else
    {
        return ((flag_limit_hi & 0xF) << 16) + limit_lo;
    }
    
}

//return the base in integer from the GDT structure
uint32 GlobalDescriptorTable::SegmentDescriptor::Base()
{
    uint32 result = (base_vhi << 24) + (base_hi << 16) + base_lo;
    if((flag_limit_hi & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;
    return result;
}