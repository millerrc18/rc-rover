# Contributing

Thank you for your interest in contributing to `rc-rover`.  This document provides guidelines for working on this repository.

## Branching

- Use short, descriptive branch names that follow the pattern `<type>/<short-description>`.  
  - Example types: `docs`, `feature`, `bugfix`, `refactor`.  
  - Example: `docs/update-roadmap`, `feature/telemetry-sensor`.
- Avoid working directly on `main`.  All work should happen on a feature branch.

## Commits

- Write clear, concise commit messages that describe what changed and why.  
- Use the imperative mood in commit messages (e.g. “Add obstacle sensor support” instead of “Added obstacle sensor support”).
- Group related changes in a single commit rather than making one large commit for multiple unrelated changes.

## Pull requests

- Open a pull request (PR) when your branch is ready for review.  
- In the PR description, summarise what was done, why, and how to test it.
- Link to any relevant issues or tasks.
- PRs should be small and focused.  Avoid mixing unrelated changes in one PR.
- Ensure that documentation is updated as part of the PR (see below).

## Documentation updates

When your work changes the state of the project, you **must** update the relevant documentation:

- **PROJECT_STATE.md** for changes to the current state.
- **NEXT_STEPS.md** for changes to the action queue.
- **DECISIONS.md** if a new decision was made.
- **LEARNINGS.md** for lessons learned.
- **BUILD_LOG.md** with a dated entry describing the work done.
- **ARCHITECTURE.md** if the architecture changed.
- **HANDOFF.md** with a fresh snapshot for the next session.

Failure to update the documentation will result in delays and confusion in future sessions.

## Code style

- Keep the codebase consistent.  Use existing formatting and naming patterns as a guide.
- Comment your code where necessary to explain non‑obvious logic.
- Favour readability and maintainability over cleverness.

## Testing

- When adding new code, provide tests or scripts to verify its functionality if applicable.
- Ensure that existing functionality continues to work.

## Code reviews

- Be open to feedback.  Reviews are an opportunity to improve the code and documentation.
- Reviewers should provide constructive comments that focus on the code and not the person.

## Reporting issues

- Use GitHub issues to report bugs, request features or ask questions.
- Provide as much detail as possible, including steps to reproduce the problem if relevant.