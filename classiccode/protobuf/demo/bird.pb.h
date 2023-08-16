// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: bird.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_bird_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_bird_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_bird_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_bird_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_bird_2eproto;
class bird;
class birdDefaultTypeInternal;
extern birdDefaultTypeInternal _bird_default_instance_;
class bird_RemarkEntry_DoNotUse;
class bird_RemarkEntry_DoNotUseDefaultTypeInternal;
extern bird_RemarkEntry_DoNotUseDefaultTypeInternal _bird_RemarkEntry_DoNotUse_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::bird* Arena::CreateMaybeMessage<::bird>(Arena*);
template<> ::bird_RemarkEntry_DoNotUse* Arena::CreateMaybeMessage<::bird_RemarkEntry_DoNotUse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class bird_RemarkEntry_DoNotUse : public ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<bird_RemarkEntry_DoNotUse, 
    std::string, std::string,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
    0 > {
public:
  typedef ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<bird_RemarkEntry_DoNotUse, 
    std::string, std::string,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
    0 > SuperType;
  bird_RemarkEntry_DoNotUse();
  bird_RemarkEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void MergeFrom(const bird_RemarkEntry_DoNotUse& other);
  static const bird_RemarkEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const bird_RemarkEntry_DoNotUse*>(&_bird_RemarkEntry_DoNotUse_default_instance_); }
  static bool ValidateKey(std::string* s) {
    return ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(s->data(), static_cast<int>(s->size()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE, "bird.RemarkEntry.key");
 }
  static bool ValidateValue(std::string* s) {
    return ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(s->data(), static_cast<int>(s->size()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE, "bird.RemarkEntry.value");
 }
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& other) final;
  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bird_2eproto);
    return ::descriptor_table_bird_2eproto.file_level_metadata[0];
  }

  public:
};

// -------------------------------------------------------------------

class bird PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:bird) */ {
 public:
  inline bird() : bird(nullptr) {};
  virtual ~bird();

  bird(const bird& from);
  bird(bird&& from) noexcept
    : bird() {
    *this = ::std::move(from);
  }

  inline bird& operator=(const bird& from) {
    CopyFrom(from);
    return *this;
  }
  inline bird& operator=(bird&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const bird& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const bird* internal_default_instance() {
    return reinterpret_cast<const bird*>(
               &_bird_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(bird& a, bird& b) {
    a.Swap(&b);
  }
  inline void Swap(bird* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(bird* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline bird* New() const final {
    return CreateMaybeMessage<bird>(nullptr);
  }

  bird* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<bird>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const bird& from);
  void MergeFrom(const bird& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(bird* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "bird";
  }
  protected:
  explicit bird(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bird_2eproto);
    return ::descriptor_table_bird_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------


  // accessors -------------------------------------------------------

  enum : int {
    kRemarkFieldNumber = 2,
    kNameFieldNumber = 1,
  };
  // map<string, string> remark = 2;
  int remark_size() const;
  private:
  int _internal_remark_size() const;
  public:
  void clear_remark();
  private:
  const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
      _internal_remark() const;
  ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
      _internal_mutable_remark();
  public:
  const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
      remark() const;
  ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
      mutable_remark();

  // string name = 1;
  void clear_name();
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  std::string* unsafe_arena_release_name();
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_name(
      std::string* name);
  private:
  const std::string& _internal_name() const;
  void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // @@protoc_insertion_point(class_scope:bird)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::MapField<
      bird_RemarkEntry_DoNotUse,
      std::string, std::string,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_STRING,
      0 > remark_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_bird_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// bird

// string name = 1;
inline void bird::clear_name() {
  name_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline const std::string& bird::name() const {
  // @@protoc_insertion_point(field_get:bird.name)
  return _internal_name();
}
inline void bird::set_name(const std::string& value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:bird.name)
}
inline std::string* bird::mutable_name() {
  // @@protoc_insertion_point(field_mutable:bird.name)
  return _internal_mutable_name();
}
inline const std::string& bird::_internal_name() const {
  return name_.Get();
}
inline void bird::_internal_set_name(const std::string& value) {
  
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void bird::set_name(std::string&& value) {
  
  name_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:bird.name)
}
inline void bird::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:bird.name)
}
inline void bird::set_name(const char* value,
    size_t size) {
  
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:bird.name)
}
inline std::string* bird::_internal_mutable_name() {
  
  return name_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* bird::release_name() {
  // @@protoc_insertion_point(field_release:bird.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void bird::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:bird.name)
}
inline std::string* bird::unsafe_arena_release_name() {
  // @@protoc_insertion_point(field_unsafe_arena_release:bird.name)
  GOOGLE_DCHECK(GetArena() != nullptr);
  
  return name_.UnsafeArenaRelease(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      GetArena());
}
inline void bird::unsafe_arena_set_allocated_name(
    std::string* name) {
  GOOGLE_DCHECK(GetArena() != nullptr);
  if (name != nullptr) {
    
  } else {
    
  }
  name_.UnsafeArenaSetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      name, GetArena());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:bird.name)
}

// map<string, string> remark = 2;
inline int bird::_internal_remark_size() const {
  return remark_.size();
}
inline int bird::remark_size() const {
  return _internal_remark_size();
}
inline void bird::clear_remark() {
  remark_.Clear();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
bird::_internal_remark() const {
  return remark_.GetMap();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >&
bird::remark() const {
  // @@protoc_insertion_point(field_map:bird.remark)
  return _internal_remark();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
bird::_internal_mutable_remark() {
  return remark_.MutableMap();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< std::string, std::string >*
bird::mutable_remark() {
  // @@protoc_insertion_point(field_mutable_map:bird.remark)
  return _internal_mutable_remark();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_bird_2eproto