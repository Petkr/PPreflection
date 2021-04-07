#pragma once
#include <list>

#include "PP/size_t.hpp"

#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"

#include "descriptor.hpp"

namespace PPreflector
{
	class namespace_function;
	class non_global_namespace;
	class Enum;
	class Class;

	class Namespace : public descriptor
	{
		PP::size_t depth;
		std::list<non_global_namespace> namespaces;
		std::list<namespace_function> functions;
		std::list<Enum> enums;
		std::list<Class> classes;

	protected:
		Namespace(PP::size_t depth);

	public:
		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		void print_layout(llvm::raw_ostream& out) const;
		void print_metadata_members(llvm::raw_ostream& out) const override final;

		non_global_namespace& add(clang::NamespaceDecl& n);
		namespace_function& add(clang::FunctionDecl& f);
		Enum& add(clang::EnumDecl& e);
		Class& add(clang::CXXRecordDecl& c);

		void remove_std();
		
		void print_tabs(llvm::raw_ostream& out) const;

		virtual void print_scoped_name_parent(llvm::raw_ostream& out) const = 0;
		virtual void print_scoped_name_as_parent(llvm::raw_ostream& out) const = 0;

	protected:
		virtual void print_name_parent(llvm::raw_ostream& out) const = 0;

	private:
		void print_namespaces(llvm::raw_ostream& out) const;
		void print_types(llvm::raw_ostream& out) const;
		void print_functions(llvm::raw_ostream& out) const;

		virtual void print_unscoped_name(llvm::raw_ostream& out) const = 0;
	};
}
