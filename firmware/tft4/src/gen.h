#pragma once
#include "Kandinsky.h"
#include "config.h"
#include "weather_prompts.h"
#include "db.h"
#include "macros.h"

Kandinsky gen;

bool gen_flag = 0;

void generate() {
    gen_flag = 1;
}

void gen_tick() {
    gen.tick();

    if (gen_flag) {
        gen_flag = 0;

        gen.setScale(DISP_SCALE);
        Text query;

        // TODO: need fix, string with weirdo symbols
        if (db[kk::use_weather_prompts].toBool()) {
            query = get_weather_prompt();
        } else {
            query = db[kk::gen_query];
        }
        
        gen.generate(
            query,
            DISP_WIDTH * DISP_SCALE,
            DISP_HEIGHT * DISP_SCALE,
            Text(gen.styles).getSub(db[kk::gen_style], ';'),
            db[kk::gen_negative]);
    }
}