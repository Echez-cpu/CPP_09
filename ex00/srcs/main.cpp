


str		trim(const str & string)
{
    size_t first = string.find_first_not_of(' ');
    if (str::npos == first)
    {
        return string;
    }
    size_t last = string.find_last_not_of(' ');
    return string.substr(first, (last - first + 1));
}





