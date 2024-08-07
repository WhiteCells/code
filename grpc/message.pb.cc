// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto
// Protobuf C++ Version: 5.26.1

#include "message.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace smart {

inline constexpr test::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        name_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        email_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        age_{0} {}

template <typename>
PROTOBUF_CONSTEXPR test::test(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct testDefaultTypeInternal {
  PROTOBUF_CONSTEXPR testDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~testDefaultTypeInternal() {}
  union {
    test _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 testDefaultTypeInternal _test_default_instance_;
}  // namespace smart
static ::_pb::Metadata file_level_metadata_message_2eproto[1];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_message_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_message_2eproto = nullptr;
const ::uint32_t
    TableStruct_message_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        PROTOBUF_FIELD_OFFSET(::smart::test, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::smart::test, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::smart::test, _impl_.name_),
        PROTOBUF_FIELD_OFFSET(::smart::test, _impl_.age_),
        PROTOBUF_FIELD_OFFSET(::smart::test, _impl_.email_),
        0,
        2,
        1,
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, 11, -1, sizeof(::smart::test)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::smart::_test_default_instance_._instance,
};
const char descriptor_table_protodef_message_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\rmessage.proto\022\005smart\"0\n\004test\022\014\n\004name\030\001"
    " \002(\t\022\013\n\003age\030\002 \002(\005\022\r\n\005email\030\003 \001(\t"
};
static ::absl::once_flag descriptor_table_message_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_message_2eproto = {
    false,
    false,
    72,
    descriptor_table_protodef_message_2eproto,
    "message.proto",
    &descriptor_table_message_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_message_2eproto::offsets,
    file_level_metadata_message_2eproto,
    file_level_enum_descriptors_message_2eproto,
    file_level_service_descriptors_message_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_message_2eproto_getter() {
  return &descriptor_table_message_2eproto;
}
namespace smart {
// ===================================================================

class test::_Internal {
 public:
  using HasBits = decltype(std::declval<test>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(test, _impl_._has_bits_);
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000005) ^ 0x00000005) != 0;
  }
};

test::test(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:smart.test)
}
inline PROTOBUF_NDEBUG_INLINE test::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : _has_bits_{from._has_bits_},
        _cached_size_{0},
        name_(arena, from.name_),
        email_(arena, from.email_) {}

test::test(
    ::google::protobuf::Arena* arena,
    const test& from)
    : ::google::protobuf::Message(arena) {
  test* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  _impl_.age_ = from._impl_.age_;

  // @@protoc_insertion_point(copy_constructor:smart.test)
}
inline PROTOBUF_NDEBUG_INLINE test::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0},
        name_(arena),
        email_(arena) {}

inline void test::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.age_ = {};
}
test::~test() {
  // @@protoc_insertion_point(destructor:smart.test)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void test::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.name_.Destroy();
  _impl_.email_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
test::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(test, _impl_._cached_size_),
              false,
          },
          &test::MergeImpl,
          &test::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void test::Clear() {
// @@protoc_insertion_point(message_clear_start:smart.test)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _impl_.name_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      _impl_.email_.ClearNonDefaultToEmpty();
    }
  }
  _impl_.age_ = 0;
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* test::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 3, 0, 28, 2> test::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(test, _impl_._has_bits_),
    0, // no _extensions_
    3, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967288,  // skipmap
    offsetof(decltype(_table_), field_entries),
    3,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_test_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::smart::test>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // required string name = 1;
    {::_pbi::TcParser::FastSS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(test, _impl_.name_)}},
    // required int32 age = 2;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(test, _impl_.age_), 2>(),
     {16, 2, 0, PROTOBUF_FIELD_OFFSET(test, _impl_.age_)}},
    // optional string email = 3;
    {::_pbi::TcParser::FastSS1,
     {26, 1, 0, PROTOBUF_FIELD_OFFSET(test, _impl_.email_)}},
  }}, {{
    65535, 65535
  }}, {{
    // required string name = 1;
    {PROTOBUF_FIELD_OFFSET(test, _impl_.name_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kRawString | ::_fl::kRepAString)},
    // required int32 age = 2;
    {PROTOBUF_FIELD_OFFSET(test, _impl_.age_), _Internal::kHasBitsOffset + 2, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kInt32)},
    // optional string email = 3;
    {PROTOBUF_FIELD_OFFSET(test, _impl_.email_), _Internal::kHasBitsOffset + 1, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kRawString | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\12\4\0\5\0\0\0\0"
    "smart.test"
    "name"
    "email"
  }},
};

::uint8_t* test::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:smart.test)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    const std::string& _s = this->_internal_name();
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(_s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormat::SERIALIZE,
                                "smart.test.name");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // required int32 age = 2;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<2>(
            stream, this->_internal_age(), target);
  }

  // optional string email = 3;
  if (cached_has_bits & 0x00000002u) {
    const std::string& _s = this->_internal_email();
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(_s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormat::SERIALIZE,
                                "smart.test.email");
    target = stream->WriteStringMaybeAliased(3, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:smart.test)
  return target;
}

::size_t test::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:smart.test)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // required string name = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_name());
  }

  // optional string email = 3;
  if (cached_has_bits & 0x00000002u) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_email());
  }

  // required int32 age = 2;
  if (cached_has_bits & 0x00000004u) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_age());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void test::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<test*>(&to_msg);
  auto& from = static_cast<const test&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:smart.test)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _this->_internal_set_name(from._internal_name());
    }
    if (cached_has_bits & 0x00000002u) {
      _this->_internal_set_email(from._internal_email());
    }
    if (cached_has_bits & 0x00000004u) {
      _this->_impl_.age_ = from._impl_.age_;
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void test::CopyFrom(const test& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:smart.test)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool test::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_impl_._has_bits_)) {
    return false;
  }
  return true;
}

void test::InternalSwap(test* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.name_, &other->_impl_.name_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.email_, &other->_impl_.email_, arena);
        swap(_impl_.age_, other->_impl_.age_);
}

::google::protobuf::Metadata test::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_message_2eproto_getter,
                                   &descriptor_table_message_2eproto_once,
                                   file_level_metadata_message_2eproto[0]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace smart
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::std::false_type _static_init_ PROTOBUF_UNUSED =
    (::_pbi::AddDescriptors(&descriptor_table_message_2eproto),
     ::std::false_type{});
#include "google/protobuf/port_undef.inc"
