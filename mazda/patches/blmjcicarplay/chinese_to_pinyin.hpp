#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "unicode_to_pinyin_data.hpp"

namespace chinese_to_pinyin_detail {
inline const char* pinyin_for_codepoint(uint32_t codepoint) {
    uint16_t pinyin_id = 0;
    if (codepoint == 0x3007u) {
        pinyin_id = kIdeographicZeroPinyinId;
    } else if (codepoint >= kPinyinFirstCodepoint &&
               codepoint <= kPinyinLastCodepoint) {
        pinyin_id = kPinyinIdByCodepoint[codepoint - kPinyinFirstCodepoint];
    }
    return pinyin_id == 0u ? nullptr : kPinyinById[pinyin_id];
}
}  // namespace chinese_to_pinyin_detail

inline std::string chinese_to_pinyin(const std::wstring& s) {
    std::string result;
    result.reserve(s.size() * 8u);
    for (auto it = s.begin(); it != s.end(); ++it) {
        const uint32_t codepoint = static_cast<uint32_t>(*it);
        const char *pinyin = chinese_to_pinyin_detail::pinyin_for_codepoint(codepoint);
        if (pinyin != nullptr) {
            result += pinyin;
            result += ' ';
        } else {
            result += static_cast<char>(*it);
        }
    }

    return result;
}
