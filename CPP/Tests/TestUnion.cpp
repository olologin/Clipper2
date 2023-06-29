#include <gtest/gtest.h>
#include "clipper2/clipper.h"
#include "ClipFileLoad.h"

#include <algorithm>
#include <fstream>


TEST(Clipper2Tests, TestUnion1)
{
  std::ifstream ifs("Union.txt");
  Clipper2Lib::Paths64 subject, subject_open, clip;
  Clipper2Lib::ClipType ct = Clipper2Lib::ClipType::None;
  Clipper2Lib::FillRule fr = Clipper2Lib::FillRule::NonZero;
  int64_t stored_area = 0, stored_count = 0;

  ASSERT_TRUE(LoadTestNum(ifs, 1, subject, subject_open, clip, stored_area, stored_count, ct, fr));

  Clipper2Lib::Paths64 solution, solution_open;
  Clipper2Lib::Clipper64 c;
  c.AddSubject(subject);
  c.AddClip(clip);
  EXPECT_TRUE(c.Execute(ct, fr, solution, solution_open));
  ASSERT_EQ(solution_open.size(), 0);

  const auto& poly = solution[1];
  // This point is not supposed to be in solution
  ASSERT_TRUE(std::find(poly.begin(), poly.end(), Clipper2Lib::Point64(76489672, -109493814)) == poly.end());
}