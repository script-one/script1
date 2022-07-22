// source file: prog/lib/obj.s1

export function copy(o)                            // (1) 
{                                                  // (1) 
    return fromJson(toJson(o));                    // (2) 
}                                                  // (1) 

