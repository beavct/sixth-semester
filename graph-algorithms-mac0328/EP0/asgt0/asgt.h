/* this file MUST NOT be edited by the students */

/*
    - This file must not be modified and not submitted

    - The functions declared here must be defined in asgt.cpp file, which must be submited

*/

#ifndef ASGT_H
#define ASGT_H

#include <iostream>
#include "arb.h"

bool is_ancestor (const Vertex& u, const Vertex& v, const HeadStart& data); /*Must be O(1)*/
HeadStart preprocess (Arb &arb, const Vertex& root); /*Must be O(n)*/
Arb read_arb(std::istream& in); /*Must be O(n)*/

#endif // #ifndef ASGT_H
