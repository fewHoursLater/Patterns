import functools

def null_decorator(func):
    return func

def uppercaseWithMetaData(func):
    @functools.wraps(func)
    def wrapper():
        return func().upper()
    return wrapper

def uppercase(func):
    def wrapper():
        original_result = func()
        modified_result = original_result.upper()
        return modified_result
    return wrapper

def strong(func):
    def wrapper():
        return '<strong>' + func() + '</strong>'
    return wrapper

def emphasis(func):
    def wrapper():
        return '<em>' + func() + '</em>'
    return wrapper

def proxy(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper


def trace(func):
    def wrapper(*args, **kwargs):
        print(f'TRACE: calling {func.__name__}() '
              f'with {args}, {kwargs}')

        original_result = func(*args, **kwargs)

        print(f'TRACE: {func.__name__}() '
              f'returned {original_result!r}')

        return original_result
    return wrapper

@trace
def say(name, line):
    return f'{name}: {line}'

@uppercaseWithMetaData
def greet():
    """Return a friendly greeting."""
    return 'Hello!'

print(greet())
print(say('Jane', 'Hello, World'))
print(greet.__name__)
print(greet.__doc__)

