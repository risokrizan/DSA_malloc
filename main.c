// zadanie1.c -- Richard Križan, 2.10.2017 11:43

#include <stdio.h>
#include <string.h>

void *p;
typedef struct Mem {
    char isFree;
    unsigned int sizes;
    struct Mem *next_free;
} MM;


MM *vytvor_novy(MM* volnyBlok,int size){
    MM *nblok;
    
    nblok = (MM *) ((char *) volnyBlok + size + sizeof(MM));
    nblok->sizes = volnyBlok->sizes-size-sizeof(MM);
    nblok->isFree = 1;
    nblok->next_free = NULL;
    return nblok;
}

void *memory_alloc(unsigned int size) {
    MM *pblok,*nblok,*ablok;
    pblok = (MM *) p;
    ablok = (MM *) p;
    //MM *tblok =(MM*) 0x7ffeefbff578;
    //printf ("A6: %d\n",tblok->sizes);
    
    while (ablok->next_free != NULL){
        if(ablok->isFree == 1 && ablok->sizes >= sizeof(MM) + size)
            break;
        ablok=ablok->next_free;
    }
    while (pblok->next_free != NULL){
        if(pblok->next_free == ablok)
            break;
        pblok=pblok->next_free;
    }
    
    if (ablok->sizes>= size + sizeof(MM)){
        //MERGE DOPREDU
        if ((MM*)((char*)ablok + ablok->sizes) == ablok->next_free && ablok->next_free != NULL ){
            ablok -> sizes = ablok->sizes + ablok->next_free->sizes;
            ablok->next_free = ablok->next_free->next_free;
        }
        //LEN ak nie je exact fit
        if ((size + sizeof(MM))!= ablok->sizes){
            nblok=vytvor_novy(ablok,size);
            pblok->next_free=nblok;
        }
        
        ablok->sizes = size + sizeof(MM);
        ablok->isFree = 0;
        //PO FREE posun
        if (pblok->next_free->isFree == 0)
            pblok->next_free = pblok->next_free->next_free;
        
        
        return ablok + 1;
    }
    else{
        printf("Uz nemallocnem");
        return NULL;
    }
}

int memory_free(void *valid_ptr) {
    MM *fblok = (MM*) valid_ptr;
    MM *zblok = (MM*) p;
    MM *pred_fblok = (MM*) p;
    
    fblok = fblok - 1;
    while (zblok->next_free < fblok){
        if (zblok->next_free == NULL)
            break;
        zblok=zblok->next_free;
    }
    
    fblok->isFree = 1;
    fblok->next_free = zblok->next_free;
    zblok->next_free = fblok;
    
    while(pred_fblok<fblok){
        pred_fblok=pred_fblok->next_free;
    }
    
    //MERGE dopredu
    if ((MM*)((char*)fblok + fblok->sizes) == fblok->next_free && fblok->next_free != NULL ){
        fblok -> sizes = fblok->sizes + fblok->next_free->sizes;
        fblok->next_free = fblok->next_free->next_free;
    }
    
    //MERGE dozadu
    if ((MM*)((char*)pred_fblok + pred_fblok->sizes) == fblok && fblok != NULL ){
        pred_fblok -> sizes = pred_fblok->sizes + fblok->sizes;
        pred_fblok->next_free = fblok->next_free;
    }
    return 0;
}

int memory_check(void *ptr) {

    if (ptr == NULL)
        return 0;
    
    MM *pblok = (MM*) p;
    MM *valid_blok = (MM*) ptr;
    valid_blok = valid_blok - 1;
    pblok = pblok + 1;
    
    while (pblok!=NULL){
        if (pblok > valid_blok)
            return 0;
        if (valid_blok == pblok && pblok->isFree == 1)
            return 0;
        if (valid_blok == pblok)
            return 1;
        
        pblok = (MM*)((char *) pblok + pblok-> sizes);
    }
    return 0;
}

void memory_init(void *ptr, unsigned int size) {
    p = ptr;
    MM *prva;
    prva = (MM*) p;
    prva->isFree=2;
    prva->sizes=size-sizeof(MM);
    prva->next_free=NULL;
    p = p + sizeof(MM);
    MM *druha;
    druha = (MM *) p;
    druha->isFree=1;
    druha->sizes = prva->sizes - sizeof(MM);
    druha->next_free=NULL;
    prva->next_free = p;
    p = p - sizeof (MM);
}



// Vlastna funkcia main() je pre vase osobne testovanie. Dolezite: pri testovacich scenaroch sa nebude spustat!
int main() {
    char region[184];
    memory_init(region, 184);
    char *pointer = (char *) memory_alloc(8);
    printf("%p\n",pointer);
    char *pointer1 = (char *) memory_alloc(8);
    printf("%p\n",pointer1);
    char *pointer2 = (char *) memory_alloc(8);
    printf("%p\n",pointer2);
    memory_free (pointer1);
    printf("FREE %p\n",pointer1);
    char *pointer3 = (char *) memory_alloc(8);
    printf("%p\n",pointer3);
    char *pointer4 = (char *) memory_alloc(8);
    printf("%p\n",pointer4);
    memory_free (pointer);
    printf("FREE %p\n",pointer);
    char *pointer5 = (char *) memory_alloc(8);
    printf("%p\n",pointer5);
    char *pointer6 = (char *) memory_alloc(8);
    printf("%p\n",pointer6);
    char *pointer7 = (char *) memory_alloc(8);
    printf("%p\n",pointer7);
    char *pointer8 = (char *) memory_alloc(8);
    printf("%p\n",pointer8);
    
    
    
    
    if(memory_check(pointer2))
        printf ("Jou jou\n");
    else
        printf("Nop Nop\n");
    
    
    
    
    
    return 0;
}
