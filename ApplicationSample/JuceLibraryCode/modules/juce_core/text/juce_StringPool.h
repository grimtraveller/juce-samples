/*
  ==============================================================================

   This file is part of the juce_core module of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission to use, copy, modify, and/or distribute this software for any purpose with
   or without fee is hereby granted, provided that the above copyright notice and this
   permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
   NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
   DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
   IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ------------------------------------------------------------------------------

   NOTE! This permissive ISC license applies ONLY to files within the juce_core module!
   All other JUCE modules are covered by a dual GPL/commercial license, so if you are
   using any other modules, be sure to check that you also comply with their license.

   For more details, visit www.juce.com

  ==============================================================================
*/

#ifndef JUCE_STRINGPOOL_H_INCLUDED
#define JUCE_STRINGPOOL_H_INCLUDED


//==============================================================================
/**
    A StringPool holds a set of shared strings, which reduces storage overheads and improves
    comparison speed when dealing with many duplicate strings.

    When you add a string to a pool using getPooledString, it'll return a character
    array containing the same string. This array is owned by the pool, and the same array
    is returned every time a matching string is asked for. This means that it's trivial to
    compare two pooled strings for equality, as you can simply compare their pointers. It
    also cuts down on storage if you're using many copies of the same string.
*/
class JUCE_API  StringPool
{
public:
    //==============================================================================
    /** Creates an empty pool. */
    StringPool() noexcept;

    /** Destructor */
    ~StringPool();

    //==============================================================================
    /** Returns a pointer to a copy of the string that is passed in.

        The pool will always return the same pointer when asked for a string that matches it.
        The pool will own all the pointers that it returns, deleting them when the pool itself
        is deleted.
    */
    String::CharPointerType getPooledString (const String& original);

    /** Returns a pointer to a copy of the string that is passed in.

        The pool will always return the same pointer when asked for a string that matches it.
        The pool will own all the pointers that it returns, deleting them when the pool itself
        is deleted.
    */
    String::CharPointerType getPooledString (const char* original);

    /** Returns a pointer to a copy of the string that is passed in.

        The pool will always return the same pointer when asked for a string that matches it.
        The pool will own all the pointers that it returns, deleting them when the pool itself
        is deleted.
    */
    String::CharPointerType getPooledString (const wchar_t* original);

    //==============================================================================
    /** Returns the number of strings in the pool. */
    int size() const noexcept;

    /** Returns one of the strings in the pool, by index. */
    String::CharPointerType operator[] (int index) const noexcept;

private:
    Array <String> strings;
    CriticalSection lock;
};


#endif   // JUCE_STRINGPOOL_H_INCLUDED
