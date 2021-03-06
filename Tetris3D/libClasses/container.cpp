//
//  container.cpp
//  Tetris3D
//
//  Created by ugo cottin on 28/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "container.hpp"

Container::Container() {
}

Container::~Container() {
}

void Container::addForm(Form addedForm) {
    forms.insert(std::make_pair(getSize(), addedForm));
};

Form* Container::getForm(int index) {
    std::map<int, Form>::iterator it = forms.begin();
    for(int i = 0; i < getSize(); i++) {
        if (i == index) {
            return &(it->second);
        }
        it++;
    }
    return NULL;
};

int Container::getSize() {
    return (int)forms.size();
};

void Container::RenderDrawContainer(SDL_Renderer* renderer, int shiftX, int shiftY) {
    std::map<int, Form>::iterator it = forms.begin();
    
    Cube*** plateau = createArray(CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
    
    while (it != forms.end()) {
        
        Point3D org = it->second.getOrigin();
        Cube*** el = it->second.getElements();
        for(int i = 0; i < FORM_MAX_SIZE; i++) {
            for(int j = 0; j < FORM_MAX_SIZE; j++) {
                for(int k = 0; k < FORM_MAX_SIZE; k++) {
                    if (el[i][j][k].doesExist())
                        plateau[(int)org.getX() + i][(int)org.getY() + j][(int)org.getZ() + k] = el[i][j][k];
                }
            }
        }
        //it->second.RenderDrawForm(renderer, shiftX, shiftY);
        it++;
    }
    
    Cube* c = new Cube;
    
    for(int i = 0; i < CONTAINER_MAX_SIZE; i++) {
        for(int j = 0; j < CONTAINER_MAX_SIZE; j++) {
            for(int k = CONTAINER_MAX_SIZE - 1; k >= 0; k--) {
                c = &plateau[i][j][k];
                if (c->doesExist()) {
                    Uint8 SavedR = 0;
                    Uint8 SavedG = 0;
                    Uint8 SavedB = 0;
                    Uint8 SavedA = 0;
                    int test = SDL_GetRenderDrawColor(renderer, &SavedR, &SavedG, &SavedB, &SavedA);
                    if (test != 0)
                        SDL_GetError();
                    
                    Uint8 r = 0;
                    Uint8 g = 0;
                    Uint8 b = 0;
                    Uint8 a = 255;
                    c->getColors(&r, &g, &b);
                    test = SDL_SetRenderDrawColor(renderer, r, g, b, a);
                    if (test != 0)
                        SDL_GetError();
                    c->RenderDrawCube(renderer, i, j, k, shiftX, shiftY);
                }
            }
        }
    }
    /*
    std::map<int, Form>::iterator it = forms.begin();
    
    while (it != forms.end()) {
        it->second.RenderDrawForm(renderer, shiftX, shiftY);
        it++;
    }*/
    
};
