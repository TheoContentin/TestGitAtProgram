#include "kart.h"

kart::kart(map map){
    vit = {map.start_direction[0],map.start_direction[1]};
    pos = map.start_position;
}
