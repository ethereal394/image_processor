#include "anime_factory.h"

#include "../exceptions.h"
#include "../filters/anime.h"

std::unique_ptr<BaseFilter> AnimeFactory::Create(const std::vector<std::string>& input_params) {
    if (!input_params.empty()) {
        throw FilterException("number of arguments of anime filter must be 0");
    }
    return std::make_unique<Anime>();
}
