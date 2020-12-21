#pragma once

#include "sc_template.hpp"

#include <memory>
#include <string>

class ScTemplateSCsBuilder final
{
public:
  explicit ScTemplateSCsBuilder(class ScMemoryContext & ctx);
  ~ScTemplateSCsBuilder();

  /*! Makes template from scs text
   * \return Returns pointer to created ScTemplate or nullptr in case of error.
   */
  ScTemplatePtr Make(std::string const & scsText);

  //! Returns error message in case of error during template creation
  std::string const & GetErrorMessage() const;

private:
  class ScMemoryContext & m_ctx;
  std::unique_ptr<class ScTemplateBuilderImpl> m_builder;
  std::string m_errorMessage;
  bool m_isDone = false;
};
