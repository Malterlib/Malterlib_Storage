# CLAUDE.md - Storage Module

This file provides guidance to Claude Code (claude.ai/code) when working with the Storage module in Malterlib.

## Module Overview

The Storage module provides advanced memory management and data storage utilities for C++ applications. It implements custom smart pointers, optional types, variants, lazy initialization patterns, and other storage-related abstractions that integrate with Malterlib's memory management system.

## Architecture

### Namespace Organization
- **NMib::NStorage** - Main storage namespace containing all primary storage utilities
- **NMib::NStorage::NReference** - Reference wrapper implementation
- **NMib::NStorage::NPrivate** - Internal implementation details

### Component Categories

#### Smart Pointers
- **TCSharedPointer** - Reference-counted smart pointer with thread-safe operations
- **TCUniquePointer** - Single-ownership smart pointer with custom allocator support
- **TCWeakPointer** - Non-owning weak reference to shared pointer objects
- **TCBitStorePointer** - Pointer that stores extra bits in unused address bits (for alignment-guaranteed allocations)
- **CAutoClearPtr** - Auto-clearing pointer for debugging reference counting issues

#### Container Types
- **TCOptional** - Optional value container (similar to std::optional)
- **TCVariant** - Type-safe discriminated union (similar to std::variant)
- **TCTuple** - Tuple implementation (wraps std::tuple with Malterlib integration)
- **TCAggregate** - Aggregate data storage with prioritized destruction

#### Memory Management
- **TCLazyInit** - Thread-safe lazy initialization pattern
- **TCIndirection** - Indirection layer for pointer-like semantics
- **TCReference** - Reference wrapper with additional safety features

### File Organization

```
Storage/
├── Include/Mib/Storage/    # Public headers for each component
│   ├── Aggregate
│   ├── AutoClearPointer
│   ├── BitStorePointer
│   ├── DebugPointer
│   ├── Indirection
│   ├── LazyInit
│   ├── Optional
│   ├── Pointer
│   ├── Reference
│   ├── SharedPointer
│   ├── Tuple
│   ├── UniquePointer
│   └── Variant
├── Source/                 # Implementation files
│   ├── Malterlib_Storage_*.h     # Main headers
│   ├── Malterlib_Storage_*.hpp   # Template implementations
│   ├── Malterlib_Storage_*.cpp   # Non-template implementations
│   └── Private/            # Internal helpers
│       ├── *_Helpers.h
│       └── *_Traits.h
└── Test/                   # Unit tests
    └── Test_Malterlib_Storage_*.cpp
```

## Key Components

### Smart Pointers

#### TCSharedPointer
- Thread-safe reference counting
- Custom allocator support
- Weak pointer support
- Debug modes for leak detection (DMibConfig_RefCountDebugging, DMibConfig_RefCountLeakDebugging)

#### TCUniquePointer
- Single ownership semantics
- Custom allocator support via template options
- Move-only semantics
- Supports polymorphic types with virtual destructors

#### TCBitStorePointer
- Stores extra bits in unused pointer bits (template parameter t_nBits)
- Default 2 bits for 32-bit system safety
- Useful for tagged pointers and compact data structures

### Container Types

#### TCOptional<t_CType>
- Inherits from TCStreamableVariant for serialization support
- Construct-in-place support via TCConstruct helper
- Conversion operators for seamless usage
- Has-value checking and value access methods

#### TCVariant<tp_CTypes...>
- Type-safe discriminated union
- Visitor pattern support
- Automatic destruction of active member
- Index-based and type-based access

#### TCLazyInit<t_CData, t_CLock>
- Thread-safe lazy initialization
- Configurable lock type (defaults to CLowLevelLockAggregate)
- Lifetime tracking flags (Constructed/Destructed)
- Construct-on-first-use pattern

### Memory Utilities

#### TCAggregate<t_CData, t_Priority, t_CLock>
- Prioritized destruction order
- Thread-safe lifetime management
- Module registration for cleanup
- Debug support for tracking lifetime issues

## Usage Patterns

### Smart Pointer Usage
```cpp
// Shared pointer construction
TCSharedPointer<CMyClass> pShared = fg_Construct(args...);

// Shared pointer with derived class
TCSharedPointer<CBase> pBase = fg_Construct<CDerived>(args...);

// Shared pointer with custom allocator
TCSharedPointer<CMyClass, CCustomAllocator> pSharedCustom = fg_Construct(args...);

// Unique pointer construction
TCUniquePointer<CMyClass> pUnique = fg_Construct(args...);

// Unique pointer with derived class
TCUniquePointer<CBase> pBaseUnique = fg_Construct<CDerived>(args...);

// Weak pointer from shared
TCWeakPointer<CMyClass> pWeak = pShared;
```

### Optional Usage
```cpp
TCOptional<int> OptValue;
OptValue = 42;
if (OptValue)
    int Value = *OptValue;
```

### Lazy Initialization
```cpp
TCLazyInit<CExpensiveObject> LazyObject;
// Object constructed on first access
CExpensiveObject &Object = *LazyObject;
```

### Variant Usage
```cpp
TCVariant<int, float, CString> Value;
Value = 42;
// Visit pattern for type-safe access
Value.f_Visit([](auto &_Value) { /* process _Value */ });
```

## Configuration Macros

### Debug Configuration

#### Compile-time Debug Macros
- **DMibConfig_RefCountDebugging** - Enable reference counting debug output (default: 0)
- **DMibConfig_RefCountLeakDebugging** - Enable leak detection for shared pointers (default: 0)
- **DIfRefCountDebugging(...)** - Conditional compilation for debug code
- **DIfNotRefCountDebugging(...)** - Inverse conditional compilation

#### Runtime Debug Settings
To enable reference counting debugging for tracking memory leaks and reference issues, uncomment these lines in `BuildSystem/Default/UserSettings.MSettings`:

```makefile
Property // Debug
{
    Malterlib_RefCountDebugging_Enable true // Set to true to enable shared pointer reference debugging
    Malterlib_RefCountLeakDebugging_Enable true // Set to true to enable tracing information about shared pointer references when displaying memory leaks
}
```

After modifying UserSettings.MSettings, regenerate and rebuild your workspace for changes to take effect.

### Variant Configuration
- **DMibStorageVariantTypeInMember(...)** - MSVC workaround for variant member types

## Testing

The module includes comprehensive unit tests in the Test/ directory:
- **Test_Malterlib_Storage_Pointer.cpp** - Smart pointer tests
- **Test_Malterlib_Storage_Indirection.cpp** - Indirection layer tests
- **Test_Malterlib_Storage_Tuple.cpp** - Tuple functionality tests
- **Test_Malterlib_Storage_Variant.cpp** - Variant tests
- **Test_Malterlib_Storage_WeakPointer.cpp** - Weak pointer specific tests

Tests use the NMib::NTest framework and cover:
- Construction/destruction patterns
- Thread safety
- Memory leak detection
- Edge cases and error conditions

## Integration with Other Modules

### Dependencies
- **Core** - Base types and macros
- **Memory** - Allocator interfaces and memory management
- **Atomic** - Atomic operations for thread-safe reference counting
- **Thread** - Lock types for synchronization
- **Meta** - Template metaprogramming utilities
- **Function** - Function binding for callbacks
- **Stream** - Serialization support for variants and optionals
- **Contract** - Debug assertions and contract checking

### Used By
- Most Malterlib modules use Storage for smart pointer management
- Container module uses Storage types for internal implementation
- Concurrency module relies on thread-safe storage patterns

## Important Notes

1. **Thread Safety**: Most storage types are thread-safe for const operations only. TCSharedPointer provides full thread safety for reference counting.

2. **Allocator Support**: Smart pointers support custom allocators that must derive from NMemory::CAllocator_Base.

3. **Debug Builds**: Enable ref count debugging macros in debug builds to catch memory leaks and lifetime issues early.

4. **Performance**: TCBitStorePointer and lazy initialization patterns are optimized for performance-critical code.

5. **Exception Safety**: All storage types provide basic exception safety guarantees, with strong guarantees for smart pointer operations.

6. **Lifetime Management**: CAutoClearPtr and aggregate patterns help manage complex object lifetimes in multi-threaded environments.

7. **Type Safety**: Variant and optional types provide compile-time type safety with runtime checking in debug builds.

8. **Memory Alignment**: TCBitStorePointer assumes proper alignment for storing bits in pointer values.

## Common Pitfalls

1. Don't mix allocators when transferring ownership between smart pointers
2. Ensure proper locking when using TCLazyInit in multi-threaded contexts
3. Be careful with TCBitStorePointer on platforms with different alignment requirements
4. Don't store references in TCOptional or TCVariant - use pointers or TCReference
5. Avoid circular references with TCSharedPointer - use TCWeakPointer to break cycles

## Best Practices

1. Prefer TCUniquePointer for single ownership scenarios
2. Use TCSharedPointer only when shared ownership is truly needed
3. Enable debug configurations during development to catch issues early
4. Use TCOptional instead of nullable pointers when null is a valid state
5. Leverage TCVariant for type-safe unions instead of void* or type erasure
6. Use TCLazyInit for expensive objects that may not be used
7. Prefer TCReference over raw references when lifetime tracking is needed
