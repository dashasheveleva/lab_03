// Copyright 2021 Daria <photodoshfy@gmail.com>

#include <gtest/gtest.h>
#include <string>
#include "SharedPtr.hpp"


TEST(SharedPtr, EmptySharedPtr) {
    SharedPtr <std::string> r;
    ASSERT_EQ(r.get(), nullptr);
}
TEST(SharedPtr, InitializationSharedPtr) {
    SharedPtr <std::string> r(new std::string{"Hello, world!"});
    ASSERT_EQ(*r, "Hello, world!");
    ASSERT_EQ(r.use_count(), 1);
}
TEST(SharedPtr, CopyConstructor) {
    const SharedPtr <std::string> r(new std::string{"Hello, world!"});
    SharedPtr <std::string> p(r);
    ASSERT_EQ(*p, "Hello, world!");
    ASSERT_EQ(p.use_count(), 2);
}
TEST(SharedPtr, MoveConstructor) {
    SharedPtr <std::string> r(new std::string{"Hello, world!"});
    SharedPtr <std::string> p(std::move(r));
    ASSERT_EQ(*p, "Hello, world!");
    ASSERT_EQ(p.use_count(), 1);
    ASSERT_EQ(r.get(), nullptr);

    SharedPtr <std::string> q(SharedPtr<std::string>(new std::string{"Hello"}));
    ASSERT_EQ(*q, "Hello");
    ASSERT_EQ(q.use_count(), 1);
}
TEST(SharedPtr, CopyAssignment) {
    SharedPtr<std::string> r(new std::string{"SharedPtr"});
    SharedPtr<std::string> p(r);
    ASSERT_EQ(*p, "SharedPtr");
    ASSERT_EQ(p.use_count(), 2);
    ASSERT_EQ(r.use_count(), 2);

    SharedPtr<std::string> q(new std::string{"ScopedPtr"});
    ASSERT_EQ(q.use_count(), 1);

    p= q;
    ASSERT_EQ(*p, "ScopedPtr");
    ASSERT_EQ(p.use_count(), 2);
    ASSERT_EQ(r.use_count(), 2);
    ASSERT_EQ(q.use_count(), 2);

    SharedPtr<std::string> *ptr_= &p;
    p= *ptr_;
    ASSERT_EQ(*p, "ScopedPtr");
    ASSERT_EQ(p.use_count(), 2);
}
TEST(SharedPtr, MoveAssignment) {
    SharedPtr <std::string> r(new std::string{"SharedPtr"});
    SharedPtr <std::string> p(r);
    ASSERT_EQ(*p, "SharedPtr");
    ASSERT_EQ(p.use_count(), 2);
    ASSERT_EQ(r.use_count(), 2);

    SharedPtr <std::string> q(new std::string{"ScopedPtr"});
    SharedPtr <std::string> z(q);
    ASSERT_EQ(*z, "ScopedPtr");
    ASSERT_EQ(z.use_count(), 2);
    ASSERT_EQ(q.use_count(), 2);

    q= std::move(p);
    ASSERT_EQ(p.operator bool(), false);
    ASSERT_EQ(r.use_count(), 2);
    ASSERT_EQ(z.use_count(), 1);

    SharedPtr <std::string> *ptr_;
    ptr_ = &q;
    q= std::move(*ptr_);
    ASSERT_EQ(*q, "SharedPtr");
    ASSERT_EQ(q.use_count(), 2);
}
TEST(SharedPtr, Reset) {
    SharedPtr <std::string> r(new std::string{"Reset"});
    ASSERT_EQ(*r, "Reset");
    ASSERT_EQ(r.use_count(), 1);

    r.reset();
    ASSERT_EQ(r.operator bool(), false);
}
TEST(SharedPtr, ResetPointer) {
    SharedPtr <std::string> r(new std::string{"ResetPointer"});
    ASSERT_EQ(*r, "ResetPointer");
    ASSERT_EQ(r.use_count(), 1);

    r.reset(new std::string{"New"});
    ASSERT_EQ(*r, "New");
    ASSERT_EQ(r.use_count(), 1);
}
TEST(SharedPtr, Swap) {
    SharedPtr <std::string> r(new std::string{"One"});
    ASSERT_EQ(*r, "One");
    ASSERT_EQ(r.use_count(), 1);
    SharedPtr <std::string> p(new std::string{"Two"});
    ASSERT_EQ(*p, "Two");
    ASSERT_EQ(p.use_count(), 1);

    r.swap(p);
    ASSERT_EQ(*p, "One");
    ASSERT_EQ(p.use_count(), 1);
    ASSERT_EQ(*r, "Two");
    ASSERT_EQ(r.use_count(), 1);
    r.swap(r);
}
TEST(SharedPtr, IsMoveConstructible) {
    EXPECT_TRUE(std ::is_move_constructible <SharedPtr<int>>());
    EXPECT_TRUE(std ::is_move_constructible <SharedPtr<std ::string>>());
}
TEST(SharedPtr, IsMoveAssignable) {
    EXPECT_TRUE(std ::is_move_assignable <SharedPtr<int>>());
    EXPECT_TRUE(std ::is_move_assignable <SharedPtr<std ::string>>());
}
