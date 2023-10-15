//
// Created by Yukio on 15/10/2023.
//

#include "../../include/tool/FtxuiTools.h"

std::vector<ftxui::Element> LsKu::FTxT::MultiLine(const std::string& originalText) {
  std::string process_data = originalText;  // 拷贝待处理字符串

  size_t line_breaker_pos;
  std::string line_breaker = "\n";
  std::vector<std::string> vectorize_lines;

  std::vector<ftxui::Element> ftxui_lines;  // 符合FTXUI规范的"多行文本"元素

  /// 将单个长多行字符串转化为向量字符串
  while ((line_breaker_pos = process_data.find(line_breaker)) != std::string::npos) {  // 寻找法定换行符
    vectorize_lines.push_back(process_data.substr(0, line_breaker_pos));  // 换行符前赋给向量字符串
    process_data.erase(0, line_breaker_pos + line_breaker.length());      // 删去处理完的字符串
  }
  vectorize_lines.push_back(process_data);  // 向向量字符串加入最后一个换行符后的文本

  /// 将向量字符串转化为"多行文本"元素
  ftxui_lines.reserve(vectorize_lines.size());  // 预先留出向量字符串数量的内存空间
  for (const auto& iterated_line : vectorize_lines) {
    ftxui_lines.push_back(ftxui::text(iterated_line));  // 向向量型元素内注入每个单行FTXUI文本
  }

  return ftxui_lines;


}