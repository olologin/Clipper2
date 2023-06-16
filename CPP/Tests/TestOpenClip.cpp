#include <gtest/gtest.h>
#include "clipper2/clipper.h"
#include "ClipFileLoad.h"
#include <fstream>

using namespace Clipper2Lib;

TEST(Clipper2Tests, DISABLED_TestOpenClipProducesSinglePoints1)
{
  std::ifstream ifs("OpenClip.txt");
  Clipper2Lib::Paths64 subject, subject_open, clip;
  Clipper2Lib::ClipType ct = Clipper2Lib::ClipType::None;
  Clipper2Lib::FillRule fr = Clipper2Lib::FillRule::NonZero;
  int64_t stored_area = 0, stored_count = 0;

  ASSERT_TRUE(LoadTestNum(ifs, 1, subject, subject_open, clip, stored_area, stored_count, ct, fr));

  Clipper2Lib::Paths64 solution, solution_open;
  Clipper64 c;
  c.AddOpenSubject(subject_open);
  c.AddClip(clip);
  EXPECT_TRUE(c.Execute(ct, fr, solution, solution_open));
  for (size_t i = 0; i < solution_open.size(); ++i)
  {
	  ASSERT_TRUE(solution_open[i].size() > 1);
  }
}