encircling - Go-style programming for C++11
===========================================

I really like Go.  It gives very clean, simple building blocks and
abstractions for building robust and understandable applications.
I've recently found myself in a job at a C++ shop, and have been
missing Go.  This is my attempt at making C++ more Go-like.


Multiple return values
----------------------

My main use of multiple return values in go is overwhelmingly for the
error-check idiom:

    resource, err := acquire_resource()
    if err != nil {
        return fmt.Errorf("acquire_resource(): %s", err)
    }
    // use resource

In C, resource would almost always be a pointer, so you can check
`resource == NULL` to see if there has been a problem.  C++ likes to
use value-types, where (unlike C pointers) the 0-representation
doesn't necessarily mean there is a problem.

It turns out we can do something almost as tidy in C++:

    auto result = Resource::acquire();
    if (result.error()) {
        log(ERROR, "Resource::acquire(): %s", result.error_msg());
        return;
    }
    auto resource = *result;
    // use resource
