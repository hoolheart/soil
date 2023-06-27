#ifndef SOIL_MISC_HPP
#define SOIL_MISC_HPP

#define SAFE_DELETE(ptr) \
    if (ptr != nullptr) { \
        delete ptr; \
        ptr = nullptr; \
    }

#endif // SOIL_MISC_HPP
