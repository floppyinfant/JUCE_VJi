# LEARN C-Language

## References

## Standards

---

## Notes

### Pointers and Memory

```c++
// Pattern 1: Always initialize pointers
char* ptr = NULL;  // NULL is the C equivalent of nullptr

// Pattern 2: Check before use
if (ptr != NULL) {
    // use ptr
}

// Pattern 3: Clear after free
free(ptr);
ptr = NULL;  // Prevent dangling pointer

// Pattern 4: Return ownership explicitly via parameters
int create_object(MyObject** out) {
    *out = (MyObject*)malloc(sizeof(MyObject));
    return (*out != NULL) ? 0 : -1;
}
```

