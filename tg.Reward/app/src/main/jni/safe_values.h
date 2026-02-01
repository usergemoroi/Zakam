#pragma once

struct safe_bool {
    int key;
    int enc_value;

    bool get() {
        return (enc_value ^ key) == 1;
    }
};

struct safe_int {
    int key;
    int enc_value;

    bool get() {
        return enc_value ^ key;
    }
};

struct safe_float
{
    int key;
    int enc_value;

    union fi
    {
        float f;
        int i;
    };

    float get()
    {
        fi v;
        v.i = (enc_value ^ key);
        return v.f;
    }
};

void write_bool ( uintptr_t ptr , int value ) {
    auto curVal = * reinterpret_cast < safe_bool * > ( ptr );

    safe_bool newVal;

    newVal.key = curVal.key;
    newVal.enc_value = value ^ curVal.key;

    memcpy ( reinterpret_cast < void * > ( ptr ) , & newVal , sizeof ( safe_bool ) );
}

void write_int ( uintptr_t ptr , int value ) {
    auto curVal = * reinterpret_cast < safe_int * > ( ptr );

    safe_int newVal;

    newVal.key = curVal.key;
    newVal.enc_value = value ^ curVal.key;

    memcpy ( reinterpret_cast < void * > ( ptr ) , & newVal , sizeof ( safe_int ) );
}

void write_short ( uintptr_t ptr, short value ) {
    auto curVal = *reinterpret_cast<safe_int*>(ptr);

    safe_int newVal;

    newVal.key = curVal.key;
    newVal.enc_value = value ^ curVal.key;

    memcpy ( reinterpret_cast < void * > ( ptr ) , & newVal , sizeof ( safe_int ) );
}

void write_float ( uintptr_t ptr , float value )
{
    auto curVal = * reinterpret_cast < safe_float * > ( ptr );

    safe_float :: fi eVal;
    eVal.f = value;

    safe_float newVal;
    newVal.key = curVal.key;
    newVal.enc_value = eVal.i ^ curVal.key;

    memcpy ( reinterpret_cast < void * > ( ptr ) , & newVal , sizeof ( safe_float ) );
}
