#include "head.h"



teacher_t ReadXml (teacher_t t[], int amount, char text[]) {
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml from memory");
        return 1;
    }
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    int pos = 0;
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ; xCur = xCur->next) {
        if (XML_ELEMENT_NODE == xCur->type) {
            for(xmlNode * xJ = xCur->children; NULL != xJ ; xJ = xJ->next) {
                if (XML_ELEMENT_NODE == xJ->type) {
                    if(strcmp(xJ->name, "chair") == 0) {
                        teacher_setFaculty(t[pos], xJ);
                        teacher_setChair (t[pos], xJ);
                        continue;
                    }
                    const char * content = xmlNodeGetContent(xJ);
                    if (strcmp(xJ->name, "name") == 0) {
                        teacher_setName(t[pos], content);
                    }
                    if (strcmp(xJ->name, "surname") == 0) {
                        teacher_setSurname(t[pos], content);
                    }
                    if (strcmp(xJ->name, "birthdate") == 0) {
                        teacher_setBirthdate(t[pos], content);
                    }
                    if (strcmp(xJ->name, "since") == 0) {
                        teacher_setSince(t[pos], content);
                    }
                    if (strcmp(xJ->name, "rating") == 0) {
                        teacher_setRating(t[pos], content);
                    }
                }
            }
            pos++;
        }
    }







}











